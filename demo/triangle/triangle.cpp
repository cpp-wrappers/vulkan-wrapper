#if 0
src_dir=`dirname ${BASH_SOURCE[0]}`

mkdir -p ${src_dir}/build

glslangValidator -e main -o ${src_dir}/build/triangle.vert.spv -V ${src_dir}/triangle.vert
glslangValidator -e main -o ${src_dir}/build/triangle.frag.spv -V ${src_dir}/triangle.frag

. ${src_dir}/../build.sh $@ --asset triangle.vert.spv --asset triangle.frag.spv

exit 1
#endif

#include "vk/instance/guarded_handle.hpp"
#include "vk/instance/layer_properties.hpp"
#include "../platform/platform.hpp"

inline vk::guarded_handle<vk::shader_module> read_shader_module(const vk::guarded_handle<vk::device>& device, const char* path) {
	auto size = platform::file_size(path);
	char src[size];
	platform::read_file(path, src, size);
	return device.create_guarded_shader_module(vk::code_size{ (uint32) size }, vk::code{ (uint32*) src } );
}

uint32 debug_report(
	flag_enum<vk::debug_report_flag>, vk::debug_report_object_type, uint64, nuint,
	int32, c_string, c_string message, void*
) {
	platform::info("[vk] ", message).new_line();
	return 0;
}

void entrypoint() {
	span required_extensions = platform::get_required_instance_extensions();

	vk::layer_name validation_layer_name{ "VK_LAYER_KHRONOS_validation" };
	bool validation_layer_is_supported = vk::is_instance_layer_supported(validation_layer_name);
	span<vk::layer_name> layers{ validation_layer_is_supported ? &validation_layer_name : nullptr, validation_layer_is_supported ? 1u : 0u };

	vk::extension_name extensions_raw[required_extensions.size() + 1]; // TODO
	span extensions{ extensions_raw, required_extensions.size() + 1 };
	
	nuint i = 0;
	for(; i < required_extensions.size(); ++i) extensions[i] = required_extensions[i];
	extensions[i] = vk::extension_name{ "VK_EXT_debug_report" };

	auto instance = vk::create_guarded_instance(layers, extensions);

	auto debug_report_callback = instance.create_guarded_debug_report_callback(
		vk::debug_report_flags{ vk::debug_report_flag::error, vk::debug_report_flag::warning, vk::debug_report_flag::information },
		debug_report 
	);

	auto surface = platform::create_surface(instance);
	auto physical_device = instance.get_first_physical_device();
	auto queue_family_index = physical_device.get_first_queue_family_index_with_capabilities(vk::queue_flag::graphics);

	platform::info("graphics family index: ", (uint32)queue_family_index).new_line();

	if(!physical_device.get_surface_support(surface, queue_family_index)) {
		platform::error("surface isn't supported").new_line();
		throw;
	}

	auto device = physical_device.create_guarded_device(
		queue_family_index,
		vk::queue_priority{ 1.0F },
		vk::extension_name{ "VK_KHR_swapchain" }
	);

	auto surface_format = physical_device.get_first_surface_format(surface);

	vk::attachment_description attachment_description {
		surface_format.format,
		vk::load_op{ vk::attachment_load_op::clear },
		vk::store_op{ vk::attachment_store_op::store },
		vk::final_layout{ vk::image_layout::present_src_khr }
	};

	array color_attachments {
		vk::color_attachment_reference{ 0, vk::image_layout::color_attachment_optimal }
	};
	
	vk::subpass_description subpass_description { color_attachments };

	vk::subpass_dependency subpass_dependency {
		vk::src_subpass{ VK_SUBPASS_EXTERNAL },
		vk::dst_subpass{ 0 },
		vk::src_stages{ vk::pipeline_stage::color_attachment_output },
		vk::dst_stages{ vk::pipeline_stage::color_attachment_output }
	};

	auto render_pass = device.create_guarded_render_pass(
		array{ subpass_description },
		array{ attachment_description },
		array{ subpass_dependency }
	);

	auto vertex_shader = read_shader_module(device, "triangle.vert.spv");
	auto fragment_shader = read_shader_module(device, "triangle.frag.spv");

	vk::pipeline_color_blend_attachment_state pcbas {
		.src_color_blend_factor = vk::blend_factor::one,
		.dst_color_blend_factor = vk::blend_factor::zero,
		.color_blend_op = vk::blend_op::add,
		.src_alpha_blend_factor = vk::blend_factor::one,
		.dst_alpha_blend_factor = vk::blend_factor::zero,
		.alpha_blend_op = vk::blend_op::add,
		.color_write_mask = { vk::color_component::r, vk::color_component::g, vk::color_component::b, vk::color_component::a }
	};

	auto pipeline_layout = device.create_guarded_pipeline_layout();

	array dynamic_states { vk::dynamic_state::viewport, vk::dynamic_state::scissor };

	auto pipeline = device.create_guarded_graphics_pipeline(
		pipeline_layout, render_pass,
		array {
			vk::pipeline_shader_stage_create_info {
				.stage{ vk::shader_stage::vertex },
				.module{ vertex_shader.handle() },
				.entry_point_name{ "main" }
			},
			vk::pipeline_shader_stage_create_info {
				.stage{ vk::shader_stage::fragment },
				.module{ fragment_shader.handle() },
				.entry_point_name{ "main" }
			}
		},
		vk::pipeline_multisample_state_create_info{},
		vk::pipeline_vertex_input_state_create_info{},
		vk::pipeline_rasterization_state_create_info {
			.polygon_mode = vk::polygon_mode::fill,
			.cull_mode = vk::cull_mode::back,
			.front_face = vk::front_face::counter_clockwise
		},
		vk::pipeline_input_assembly_state_create_info {
			.topology = vk::primitive_topology::triangle_list
		},
		vk::pipeline_color_blend_state_create_info {
			.logic_op = vk::logic_op::copy,
			.attachment_count = 1,
			.attachments = &pcbas
		},
		vk::pipeline_viewport_state_create_info {
			.viewport_count = 1,
			.scissor_count = 1
		},
		vk::pipeline_dynamic_state_create_info {
			.dynamic_state_count = dynamic_states.size(),
			.dynamic_states = dynamic_states.data()
		},
		vk::subpass{ 0 }
	);

	auto command_pool = device.create_guarded_command_pool(queue_family_index);
	auto swapchain = vk::guarded_handle<vk::swapchain>{};

	while(!platform::should_close()) {
		auto surface_capabilities = physical_device.get_surface_capabilities(surface);

		{
			auto old_swapchain = move(swapchain);

			swapchain = device.create_guarded_swapchain(
				surface,
				surface_capabilities.min_image_count,
				surface_capabilities.current_extent,
				surface_format,
				vk::image_usages{ vk::image_usage::color_attachment, vk::image_usage::transfer_dst },
				vk::sharing_mode::exclusive,
				vk::present_mode::mailbox,
				vk::clipped{ true },
				vk::surface_transform::identity,
				vk::composite_alpha::opaque,
				old_swapchain
			);
		}

		uint32 images_count = (uint32)swapchain.get_image_count();

		vk::handle<vk::image> images_storage[images_count];
		span images{ images_storage, images_count };
		swapchain.get_images(images);

		vk::guarded_handle<vk::image_view> image_views_raw[images_count];
		span image_views{ image_views_raw, images_count };

		for(nuint i = 0; i < images_count; ++i) {
			image_views[i] = device.create_guarded_image_view(
				images[i],
				surface_format.format,
				vk::image_view_type::two_d,
				vk::component_mapping{},
				vk::image_subresource_range{ vk::image_aspect::color }
			);
		}

		vk::guarded_handle<vk::framebuffer> framebuffers_raw[images_count];
		span framebuffers{ framebuffers_raw, images_count };

		for(nuint i = 0; i < images_count; ++i) {
			framebuffers[i] = device.create_guarded_framebuffer(
				render_pass,
				array{ vk::handle<vk::image_view>{ image_views[i].handle() } },
				vk::extent<3>{ surface_capabilities.current_extent.width(), surface_capabilities.current_extent.height(), 1 }
			);
		}

		vk::handle<vk::command_buffer> command_buffers_storage[images_count];
		span command_buffers{ command_buffers_storage, images_count };
		command_pool.allocate_command_buffers(vk::command_buffer_level::primary, command_buffers);

		for(nuint i = 0; i < images_count; ++i) {
			auto command_buffer = command_buffers[i];

			command_buffer.begin(vk::command_buffer_usage::simultaneius_use);

			vk::clear_value clear_value{ vk::clear_color_value{ 0.0, 0.0, 0.0, 0.0 } };
			command_buffer.cmd_begin_render_pass(vk::render_pass_begin_info {
				.render_pass{ render_pass.handle() },
				.framebuffer{ framebuffers[i].handle() },
				.render_area{ .extent = surface_capabilities.current_extent },
				.clear_value_count = 1,
				.clear_values = &clear_value
			});

			command_buffer.cmd_bind_pipeline(pipeline);

			command_buffer.cmd_set_viewport(surface_capabilities.current_extent);
			command_buffer.cmd_set_scissor(surface_capabilities.current_extent);

			command_buffer.cmd_draw(3, 1, 0, 0);
			command_buffer.cmd_end_render_pass();

			command_buffer.end();
		}

		auto swapchain_image_semaphore = device.create_guarded_semaphore();
		auto rendering_finished_semaphore = device.create_guarded_semaphore();

		auto queue = device.get_queue(queue_family_index, vk::queue_index{ 0 });

		while (!platform::should_close()) {
			platform::begin();

			auto result = swapchain.try_acquire_next_image(vk::timeout{ UINT64_MAX }, swapchain_image_semaphore.handle());

			if(result.is_current<vk::result>()) {
				vk::result r = result.get<vk::result>();

				if(r.suboptimal() || r.out_of_date()) break;
				platform::error("can't acquire next swapchain image").new_line();
				throw;
			}

			vk::image_index image_index = result.get<vk::image_index>();

			queue.submit(
				vk::wait_semaphore{ swapchain_image_semaphore.handle() },
				vk::pipeline_stages{ vk::pipeline_stage::color_attachment_output },
				command_buffers[(uint32)image_index],
				vk::signal_semaphore{ rendering_finished_semaphore.handle() }
			);

			vk::result present_result = queue.try_present(vk::wait_semaphore{ rendering_finished_semaphore.handle() }, swapchain.handle(), image_index);

			if(!present_result.success()) {
				if(present_result.suboptimal() || present_result.out_of_date()) break;
				platform::error("can't present").new_line();
				throw;
			}

			platform::end();
		}

		device.wait_idle();

		command_pool.free_command_buffers(command_buffers);
	}
}