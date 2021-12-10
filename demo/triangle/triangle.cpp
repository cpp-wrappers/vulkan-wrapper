#if 0
src_dir=`dirname ${BASH_SOURCE[0]}`

mkdir -p ${src_dir}/build

glslangValidator -e main -o ${src_dir}/build/triangle.vert.spv -V ${src_dir}/triangle.vert
glslangValidator -e main -o ${src_dir}/build/triangle.frag.spv -V ${src_dir}/triangle.frag

. ${src_dir}/../build.sh $@ --asset triangle.vert.spv --asset triangle.frag.spv

exit 1
#endif

#include "vk/instance/guard.hpp"
#include "vk/physical_device/handle.hpp"
#include "vk/instance/layer_properties.hpp"
#include "vk/device/guard.hpp"
#include "vk/surface/guard.hpp"
#include "vk/swapchain/guard.hpp"
#include "vk/render_pass/attachment_description.hpp"
#include "vk/render_pass/subpass_description.hpp"
#include "vk/render_pass/create.hpp"
#include "vk/image/view/create.hpp"
#include "vk/framebuffer/create.hpp"
#include "vk/pipeline/create.hpp"
#include "vk/shader/module/guard.hpp"
#include "vk/pipeline/layout/create.hpp"
#include "vk/semaphore/guard.hpp"
#include "vk/debug/report/callback/create.hpp"

#include <string.h>
#include <stdio.h>
#include "../platform/platform.hpp"

vk::shader_module_guard read_shader_module(const vk::device_guard& device, const char* path) {
	auto size = platform::file_size(path);
	char src[size];
	platform::read_file(path, src, size);

	return {
		device.create_shader_module(
			vk::code_size{ (uint32) size },
			vk::code{ (uint32*) src }
		),
		device.object()
	};
}

int entrypoint() {
	nuint required_extension_count = platform::required_instance_extension_count();
	span required_extensions {
		(vk::extension_name*)platform::get_required_instance_extensions(),
		platform::required_instance_extension_count()
	};

	platform::info("required extensions:\n");
	for(vk::extension_name extension_name: required_extensions) {
		platform::info(extension_name.begin());
		platform::info('\n');
	}

	bool validation_layer_is_supported = false;
	vk::layer_name validation_layer_name{ "VK_LAYER_KHRONOS_validation" };

	vk::view_instance_layer_properties([&](span<vk::layer_properties> props) {
		for(vk::layer_properties p : props) {
			if(strcmp(p.name, validation_layer_name.begin()) == 0) {
				validation_layer_is_supported = true;
				return;
			}
		}
	});

	span<vk::layer_name> layers{ validation_layer_is_supported ? &validation_layer_name : nullptr, validation_layer_is_supported ? 1u : 0u };

	vk::extension_name extensions_raw[required_extension_count + 1]; // TODO
	span extensions{ extensions_raw, required_extension_count + 1 };
	
	nuint i = 0;
	for(; i < required_extension_count; ++i) extensions[i] = required_extensions[i];
	extensions[i++] = vk::extension_name{ "VK_EXT_debug_report" };

	vk::instance_guard instance {
		layers,
		extensions
	};

	vk::create_debug_report_callback(
		instance.object(),
		vk::debug_report_flags{
			vk::debug_report_flag::error,
			vk::debug_report_flag::warning,
			vk::debug_report_flag::information
		},
		(vk::debug_report_callback_type) [](
			flag_enum<vk::debug_report_flag> flags,
			vk::debug_report_object_type objectType,
			uint64 object,
			nuint location,
			int32 message_code,
			c_string layer_prefix,
			c_string message,
			void* user_data
		) {
			platform::info("[vk] ");
			platform::info(message.begin());
			platform::info("\n");
			return uint32{ 0 };
		}
	);

	auto surface_raw = platform::try_create_surface(instance.object());
	if(!surface_raw.is_current<vk::surface>()) {
		platform::error(surface_raw.get<c_string>().begin());
		return -1;
	}

	vk::physical_device physical_device = instance.get_first_physical_device();

	vk::queue_family_index queue_family_index {
		physical_device.get_first_queue_family_index_with_capabilities(vk::queue_flag::graphics)
	};

	platform::info("graphics family index: ", (uint32)queue_family_index, '\n');

	vk::surface_guard surface { surface_raw.get<vk::surface>(), instance.object()};

	if(!physical_device.get_surface_support(surface.object(), queue_family_index)) {
		platform::error("surface is not supported\n");
		return -1;
	}

	vk::surface_format surface_format = physical_device.get_first_surface_format(surface.object());

	vk::surface_capabilities surface_capabilities = physical_device.get_surface_capabilities(surface.object());

	vk::device_guard device = physical_device.create_device(
		queue_family_index,
		array { vk::queue_priority{ 1.0F } },
		array { vk::extension_name { "VK_KHR_swapchain" } }
	);

	vk::swapchain_guard swapchain {
		device.object(),
		surface.object(),
		surface_capabilities.min_image_count,
		surface_capabilities.current_extent,
		surface_format,
		vk::image_usages{ vk::image_usage::color_attachment, vk::image_usage::transfer_dst },
		vk::sharing_mode::exclusive,
		vk::present_mode::mailbox,
		vk::clipped{ true },
		vk::surface_transform::identity,
		vk::composite_alpha::opaque
	};

	platform::info("created swapchain\n");

	uint32 images_count = (uint32)swapchain.get_image_count();

	platform::info("swapchain images: ", images_count, '\n');

	vk::image images_storage[images_count];
	span images{ images_storage, images_count };

	swapchain.get_images(images);

	vk::attachment_description attachment_description {
		surface_format.format,
		vk::load_op{ vk::attachment_load_op::clear },
		vk::store_op{ vk::attachment_store_op::store },
		vk::initial_layout{ vk::image_layout::undefined },
		vk::final_layout{ vk::image_layout::present_src_khr }
	};
	array color_attachments {
		vk::color_attachment_reference{ 0, vk::image_layout::color_attachment_optimal }
	};
	vk::subpass_description subpass_description { color_attachments };

	vk::subpass_dependency subpass_dependency{
		vk::src_subpass{ VK_SUBPASS_EXTERNAL },
		vk::dst_subpass{ 0 },
		vk::src_stages{ vk::pipeline_stage::color_attachment_output },
		vk::dst_stages{ vk::pipeline_stage::color_attachment_output }
	};

	vk::render_pass render_pass = vk::create_render_pass(
		device.object(),
		array{ subpass_description },
		array{ attachment_description },
		array{ subpass_dependency }
	);

	vk::image_view image_views_raw[images_count];
	span image_views{ image_views_raw, images_count };

	for(nuint i = 0; i < images_count; ++i) {
		image_views[i] = vk::create_image_view(
			device.object(),
			images[i],
			surface_format.format,
			vk::image_view_type::two_d,
			vk::component_mapping{},
			vk::image_subresource_range{ vk::image_aspect::color }
		);
	}

	vk::framebuffer framebuffers_raw[images_count];
	span framebuffers{ framebuffers_raw, images_count };

	for(nuint i = 0; i < images_count; ++i) {
		framebuffers[i] = vk::create_framebuffer(
			device.object(),
			render_pass,
			array{ image_views[i] },
			vk::extent<3>{ 300, 300, 1 }
		);
	}

	auto vertex_shader = read_shader_module(device, "triangle.vert.spv");
	auto fragment_shader = read_shader_module(device, "triangle.frag.spv");

	array shader_stages {
		vk::pipeline_shader_stage_create_info {
			.stage{ vk::shader_stage::vertex },
			.module{ vertex_shader.object() },
			.entry_point_name{ "main" }
		},
		vk::pipeline_shader_stage_create_info {
			.stage{ vk::shader_stage::fragment },
			.module{ fragment_shader.object() },
			.entry_point_name{ "main" }
		}
	};

	vk::pipeline_vertex_input_state_create_info pvisci {};
	vk::pipeline_input_assembly_state_create_info piasci {
		.topology = vk::primitive_topology::triangle_list
	};

	vk::viewport viewport {
		.width = 300, .height = 300
	};

	vk::rect2d scissor {
		.offset{ 0, 0 },
		.extent{ 300, 300 }
	};

	vk::pipeline_viewport_state_create_info pvsci {
		.viewport_count = 1,
		.viewports = &viewport,
		.scissor_count = 1,
		.scissors = &scissor
	};

	vk::pipeline_rasterization_state_create_info prsci {
		.polygon_mode = vk::polygon_mode::fill,
		.cull_mode = vk::cull_mode::back,
		.front_face = vk::front_face::counter_clockwise
	};

	vk::pipeline_multisample_state_create_info pmsci {};

	vk::pipeline_color_blend_attachment_state pcbas {
		.src_color_blend_factor = vk::blend_factor::one,
		.dst_color_blend_factor = vk::blend_factor::zero,
		.color_blend_op = vk::blend_op::add,
		.src_alpha_blend_factor = vk::blend_factor::one,
		.dst_alpha_blend_factor = vk::blend_factor::zero,
		.alpha_blend_op = vk::blend_op::add,
		.color_write_mask = { vk::color_component::r, vk::color_component::g, vk::color_component::b, vk::color_component::a }
	};

	vk::pipeline_color_blend_state_create_info pcbsci {
		.logic_op = vk::logic_op::copy,
		.attachment_count = 1,
		.attachments = &pcbas
	};

	vk::pipeline_layout pipeline_layout = vk::create_pipeline_layout(device.object());

	vk::pipeline pipeline = vk::create_graphics_pipeline(
		device.object(),
		shader_stages,
		pvisci,
		piasci,
		pvsci,
		prsci,
		pmsci,
		pcbsci,
		pipeline_layout,
		render_pass,
		vk::subpass{ 0 }
	);

	vk::command_pool_guard command_pool = device.create_guarded_command_pool(queue_family_index);
	vk::command_buffer command_buffers_storage[images_count];
	span<vk::command_buffer> command_buffers{ command_buffers_storage, images_count };
	command_pool.allocate_command_buffers(vk::command_buffer_level::primary, command_buffers);

	vk::clear_value clear_value{ vk::clear_color_value{ 0.0, 0.0, 0.0, 0.0 } };

	for(nuint i = 0; i < images_count; ++i) {
		auto command_buffer = command_buffers[i];

		command_buffer.begin(vk::command_buffer_usage::simultaneius_use);

		command_buffer.cmd_begin_render_pass(vk::render_pass_begin_info {
			.render_pass{ render_pass },
			.framebuffer{ framebuffers[i] },
			.render_area {
				.offset{ 0, 0 },
				.extent{ 300, 300 }
			},
			.clear_value_count = 1,
			.clear_values = &clear_value
		});

		command_buffer.cmd_bind_pipeline(pipeline);
		command_buffer.cmd_draw(3, 1, 0, 0);
		command_buffer.cmd_end_render_pass();

		command_buffer.end();
	}

	vk::semaphore_guard swapchain_image_semaphore { device.object() };
	vk::semaphore_guard rendering_finished_semaphore { device.object() };

	vk::queue queue = device.get_queue(queue_family_index, vk::queue_index{ 0 });

	while (!platform::should_close()) {
		platform::begin();

		auto result = swapchain.try_acquire_next_image(vk::timeout{ UINT64_MAX }, swapchain_image_semaphore.object());

		if(result.is_current<vk::result>()) {
			vk::result r = result.get<vk::result>();

			if((int32)r == VK_SUBOPTIMAL_KHR) break;
			platform::error("can't acquire swapchain image\n");
			return -1;
		}

		vk::image_index image_index = result.get<vk::image_index>();

		vk::pipeline_stage wait_dst_stage_mask = vk::pipeline_stage::color_attachment_output;

		queue.submit(vk::submit_info {
			.wait_semaphore_count = 1,
			.wait_semaphores = &swapchain_image_semaphore.object(),
			.wait_dst_stage_mask = &wait_dst_stage_mask,
			.command_buffer_count = 1,
			.command_buffers = &command_buffers[(uint32)image_index],
			.signal_semaphore_count = 1,
			.signal_semaphores = &rendering_finished_semaphore.object()
		});

		queue.present(vk::present_info {
			.wait_semaphore_count = 1,
			.wait_semaphores = &rendering_finished_semaphore.object(),
			.swapchain_count = 1,
			.swapchains = &swapchain.object(),
			.image_indices = &image_index
		});

		platform::end();
	}

	device.wait_idle();

	command_pool.free_command_buffers(command_buffers);

	return 0;
}