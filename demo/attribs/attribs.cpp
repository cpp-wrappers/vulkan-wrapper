#if 0
src_dir=`dirname ${BASH_SOURCE[0]}`

mkdir -p ${src_dir}/build

glslangValidator -e main -o ${src_dir}/build/attribs.vert.spv -V ${src_dir}/attribs.vert
glslangValidator -e main -o ${src_dir}/build/attribs.frag.spv -V ${src_dir}/attribs.frag

. ${src_dir}/../build.sh $@ --asset attribs.vert.spv --asset attribs.frag.spv

exit 1
#endif

#include "vk/instance/guarded_handle.hpp"
#include "vk/instance/layer_properties.hpp"
#include "../platform/platform.hpp"

inline vk::guarded_handle<vk::shader_module> read_shader_module(const vk::guarded_handle<vk::device>& device, const char* path) {
	auto size = platform::file_size(path);
	char src[size];
	platform::read_file(path, src, size);
	return device.create_guarded<vk::shader_module>(vk::code_size{ (uint32) size }, vk::code{ (uint32*) src } );
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

	auto debug_report_callback = instance.create_guarded<vk::debug_report_callback>(
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

	auto render_pass = device.create_guarded<vk::render_pass>(
		array{ subpass_description },
		array{ attachment_description },
		array{ subpass_dependency }
	);

	auto vertex_shader = read_shader_module(device, "attribs.vert.spv");
	auto fragment_shader = read_shader_module(device, "attribs.frag.spv");

	vk::pipeline_color_blend_attachment_state pcbas {
		.src_color_blend_factor = vk::blend_factor::one,
		.dst_color_blend_factor = vk::blend_factor::zero,
		.color_blend_op = vk::blend_op::add,
		.src_alpha_blend_factor = vk::blend_factor::one,
		.dst_alpha_blend_factor = vk::blend_factor::zero,
		.alpha_blend_op = vk::blend_op::add,
		.color_write_mask = { vk::color_component::r, vk::color_component::g, vk::color_component::b, vk::color_component::a }
	};

	auto pipeline_layout = device.create_guarded<vk::pipeline_layout>();

	array dynamic_states { vk::dynamic_state::viewport, vk::dynamic_state::scissor };

	struct data_t {
		float position[4];
		float color[4];
	};

	data_t data[] = {
		{ { -0.5,  0.5, 0.0, 1.0 }, { 1.0, 0.0, 0.0, 1.0 } },
		{ {  0.5,  0.5, 0.0, 1.0 }, { 1.0, 1.0, 1.0, 1.0 } },
		{ { -0.5, -0.5, 0.0, 1.0 }, { 1.0, 1.0, 1.0, 1.0 } },
		{ {  0.5, -0.5, 0.0, 1.0 }, { 0.0, 0.0, 1.0, 1.0 } }
	};

	auto buffer = device.create_guarded<vk::buffer>(
		vk::buffer_size{ sizeof(data) },
		vk::buffer_usages{ vk::buffer_usage::vertex_buffer },
		vk::sharing_mode::exclusive
	);

	vk::vertex_input_binding_description vertex_binding_description {
		vk::binding{ 0 },
		vk::stride{ sizeof(data_t) },
	};

	array vertex_input_attribute_descriptions {
		vk::vertex_input_attribute_description {
			vk::location{ 0 },
			vk::binding{ 0 },
			vk::format::r32_g32_b32_a32_sfloat,
			vk::offset<1>{ __builtin_offsetof(data_t, position) }
		},
		vk::vertex_input_attribute_description {
			vk::location{ 1 },
			vk::binding{ 0 },
			vk::format::r32_g32_b32_a32_sfloat,
			vk::offset<1>{ __builtin_offsetof(data_t, color) }
		}
	};

	auto buff_requirements = device.get_buffer_memory_requirements(buffer);
	auto memory_props = physical_device.get_memory_properties();
	vk::guarded_handle<vk::device_memory> device_memory{};

	for(uint32 i = 0; i < memory_props.memory_type_count; ++i) {
		if(buff_requirements.memory_type_bits & (1 << i) && memory_props.memory_types[i].properties.get(vk::memory_property::host_visible)) {
			device_memory = device.allocate_guarded<vk::device_memory>(buff_requirements.size, vk::memory_type_index{i} );
			break;
		}
	}

	if(!device_memory.handle().value) throw;

	device.handle().bind_buffer_memory(buffer, device_memory);

	uint8* ptr;
	device.handle().map_memory(device_memory, vk::device_size{0}, vk::device_size{sizeof(data)}, (void**)&ptr);

	for(nuint i = 0; i < sizeof(data); ++i) *ptr++ = ((uint8*)&data)[i];

	device.handle().flush_mapped_memory_ranges(
		array{
			vk::mapped_memory_range {
				.memory{ device_memory.handle() },
				.offset{ 0 },
				.size{ sizeof(data) }
			}
		}
	);

	device.handle().unmap_memory(device_memory);

	auto pipeline = device.create_guarded<vk::graphics_pipeline>(
		pipeline_layout, render_pass,
		vk::primitive_topology::triangle_strip,
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
		vk::pipeline_vertex_input_state_create_info{
			.vertex_binding_description_count = 1,
			.vertex_binding_descriptions = &vertex_binding_description,
			.vertex_attribute_description_count = 2,
			.vertex_attribute_descriptions = vertex_input_attribute_descriptions.data()
		},
		vk::pipeline_rasterization_state_create_info {
			.polygon_mode = vk::polygon_mode::fill,
			.cull_mode = vk::cull_mode::back,
			.front_face = vk::front_face::counter_clockwise
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

	auto command_pool = device.create_guarded<vk::command_pool>(
		queue_family_index,
		vk::command_pool_create_flag::reset_command_buffer,
		vk::command_pool_create_flag::transient
	);

	struct rendering_resource {
		vk::guarded_handle<vk::command_buffer> command_buffer{};
		vk::guarded_handle<vk::semaphore> image_acquire{};
		vk::guarded_handle<vk::semaphore> finish{};
		vk::guarded_handle<vk::fence> fence{};
		vk::guarded_handle<vk::framebuffer> framebuffer{};
	};

	array<rendering_resource, 2> rendering_resources{};

	for(auto& rr : rendering_resources) {
		rr.command_buffer = command_pool.allocate_guarded<vk::command_buffer>(vk::command_buffer_level::primary);
	}

	vk::guarded_handle<vk::swapchain> swapchain{};
	auto queue = device.get_queue(queue_family_index, vk::queue_index{ 0 });

	while(!platform::should_close()) {
		auto surface_capabilities = physical_device.get_surface_capabilities(surface);

		{
			auto old_swapchain = move(swapchain);

			swapchain = device.create_guarded<vk::swapchain>(
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
			image_views[i] = device.create_guarded<vk::image_view>(
				images[i],
				surface_format.format,
				vk::image_view_type::two_d,
				vk::component_mapping{},
				vk::image_subresource_range{ vk::image_aspect::color }
			);
		}

		nuint rendering_resource_index = 0;

		for(auto& rr : rendering_resources) {
			rr.fence = device.create_guarded<vk::fence>(vk::fence_create_flags{ vk::fence_create_flag::signaled });
			rr.image_acquire = device.create_guarded<vk::semaphore>();
			rr.finish = device.create_guarded<vk::semaphore>();
		}

		while (!platform::should_close()) {
			platform::begin();

			auto& rr = rendering_resources[rendering_resource_index];
			if(++rendering_resource_index >= 2) rendering_resource_index = 0;

			device.handle().wait_for_fences(array{ rr.fence.handle() }, true, vk::timeout{ UINT64_MAX });
			device.handle().reset_fences(array{ rr.fence.handle() });

			auto result = swapchain.try_acquire_next_image(vk::timeout{ UINT64_MAX }, rr.image_acquire.handle());

			if(result.is_current<vk::result>()) {
				vk::result r = result.get<vk::result>();
				if(r.suboptimal() || r.out_of_date()) break;
				platform::error("can't acquire next swapchain image").new_line();
				throw;
			}

			vk::image_index image_index = result.get<vk::image_index>();

			rr.framebuffer = device.create_guarded<vk::framebuffer>(
				render_pass,
				array{ image_views[(uint32)image_index].handle() },
				vk::extent<3>{ surface_capabilities.current_extent.width(), surface_capabilities.current_extent.height(), 1 }
			);

			auto& command_buffer = rr.command_buffer;

			command_buffer.begin(vk::command_buffer_usage::one_time_submit);

			vk::clear_value clear_value{ vk::clear_color_value{ 0.0, 0.0, 0.0, 0.0 } };
			command_buffer.cmd_begin_render_pass(vk::render_pass_begin_info {
				.render_pass{ render_pass.handle() },
				.framebuffer{ rr.framebuffer.handle() },
				.render_area{ .extent = surface_capabilities.current_extent },
				.clear_value_count = 1,
				.clear_values = &clear_value
			});

			command_buffer.cmd_bind_pipeline(pipeline);

			command_buffer.cmd_set_viewport(surface_capabilities.current_extent);
			command_buffer.cmd_set_scissor(surface_capabilities.current_extent);

			vk::device_size offset{ 0 };
			command_buffer.cmd_bind_vertex_buffers(0, 1, &buffer.handle(), &offset);

			command_buffer.cmd_draw(4, 1, 0, 0);
			command_buffer.cmd_end_render_pass();

			command_buffer.end();

			queue.submit(
				vk::wait_semaphore{ rr.image_acquire.handle() },
				vk::pipeline_stages{ vk::pipeline_stage::color_attachment_output },
				command_buffer.handle(),
				vk::signal_semaphore{ rr.finish.handle() },
				rr.fence.handle()
			);

			vk::result present_result = queue.try_present(
				vk::wait_semaphore{ rr.finish.handle() },
				swapchain.handle(),
				image_index
			);

			if(!present_result.success()) {
				if(present_result.suboptimal() || present_result.out_of_date()) break;
				platform::error("can't present").new_line();
				throw;
			}

			platform::end();
		}

		device.wait_idle();
	}
}