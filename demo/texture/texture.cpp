#if 0
src_dir=`dirname ${BASH_SOURCE[0]}`

mkdir -p ${src_dir}/build

glslangValidator -e main -o ${src_dir}/build/texture.vert.spv -V ${src_dir}/texture.vert
glslangValidator -e main -o ${src_dir}/build/texture.frag.spv -V ${src_dir}/texture.frag
cp ${src_dir}/leaf.png ${src_dir}/build/leaf.png

. ${src_dir}/../build.sh $@ --asset texture.vert.spv --asset texture.frag.spv --asset leaf.png

exit 0
#endif

#include "../platform/platform.hpp"

void entrypoint() {
	auto instance = platform::create_instance();
	auto surface = platform::create_surface(instance);
	vk::handle<vk::physical_device> physical_device = instance.get_first_physical_device();
	auto queue_family_index = physical_device.get_first_queue_family_index_with_capabilities(vk::queue_flag::graphics);

	platform::info("graphics family index: ", (uint32)queue_family_index).new_line();

	if(!physical_device.get_surface_support(surface, queue_family_index)) {
		platform::error("surface isn't supported").new_line();
		return;
	}

	auto device = physical_device.create_guarded_device(
		queue_family_index,
		vk::queue_priority{ 1.0F },
		vk::extension_name{ "VK_KHR_swapchain" }
	);

	platform::image_info image_info = platform::read_image_info("leaf.png");
	platform::info("image width: ", image_info.width, ", height: ", image_info.height, ", size: ", image_info.size).new_line();
	char image_data_storage[image_info.size];
	span image_data{ image_data_storage, image_info.size };
	platform::read_image_data("leaf.png", image_data);

	auto image = device.create_guarded<vk::image>(
		vk::image_create_flags{},
		vk::image_type::two_d,
		vk::format::r8_g8_b8_a8_unorm,
		vk::extent<3>{ image_info.width, image_info.height, 1 },
		vk::mip_levels{ 1 },
		vk::array_layers{ 1 },
		vk::sample_count{ 1 },
		vk::image_tiling::optimal,
		vk::image_usages{
			vk::image_usage::transfer_dst,
			vk::image_usage::sampled
		},
		vk::sharing_mode::exclusive,
		span<vk::queue_family_index>{ nullptr, 0 },
		vk::initial_layout{ vk::image_layout::undefined }
	);

	auto image_memory = device.allocate_guarded<vk::device_memory>(
		vk::device_size{ image_info.size },
		physical_device.get_index_of_first_memory_type(
			vk::memory_properties{ vk::memory_property::device_local },
			device.get_image_memory_requirements(image).memory_type_bits
		)
	);

	image.bind_memory(image_memory);

	auto staging_buffer = device.create_guarded<vk::buffer>(
		vk::buffer_size{ image_info.size },
		vk::buffer_usages{ vk::buffer_usage::transfer_src },
		vk::sharing_mode::exclusive
	);

	auto staging_buffer_memory = device.allocate_guarded<vk::device_memory>(
		vk::device_size{ image_info.size },
		physical_device.get_index_of_first_memory_type(
			vk::memory_properties{ vk::memory_property::host_visible },
			device.get_buffer_memory_requirements(staging_buffer).memory_type_bits
		)
	);

	staging_buffer.bind_memory(staging_buffer_memory);

	uint8* image_data_ptr;
	staging_buffer_memory.map(vk::memory_size{ image_info.size }, (void**)&image_data_ptr);
	for(unsigned i = 0; i < image_info.size; ++i) image_data_ptr[i] = image_data[i];
	staging_buffer_memory.flush_mapped(vk::memory_size{ image_info.size });
	staging_buffer_memory.unmap();

	auto image_view = device.create_guarded<vk::image_view>(
		image,
		vk::format::r8_g8_b8_a8_unorm,
		vk::image_view_type::two_d,
		vk::component_mapping{},
		vk::image_subresource_range{ vk::image_aspects{ vk::image_aspect::color } }
	);

	struct data_t {
		float position[4];
		float tex[2];
	};

	data_t data[] = {
		{ { -0.5,  0.5, 0.0, 1.0 }, { 0.0, 1.0 } },
		{ {  0.5,  0.5, 0.0, 1.0 }, { 1.0, 1.0 } },
		{ { -0.5, -0.5, 0.0, 1.0 }, { 0.0, 0.0 } },
		{ {  0.5, -0.5, 0.0, 1.0 }, { 1.0, 0.0 } }
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
			vk::offset{ __builtin_offsetof(data_t, position) }
		},
		vk::vertex_input_attribute_description {
			vk::location{ 1 },
			vk::binding{ 0 },
			vk::format::r32_g32_sfloat,
			vk::offset{ __builtin_offsetof(data_t, tex) }
		}
	};

	vk::guarded_handle<vk::device_memory> device_memory = device.allocate_guarded<vk::device_memory>(
		physical_device.get_index_of_first_memory_type(
			vk::memory_properties{ vk::memory_property::host_visible },
			device.get_buffer_memory_requirements(buffer).memory_type_bits
		),
		vk::device_size{ sizeof(data) }
	);

	buffer.bind_memory(device_memory);

	uint8* ptr;
	device_memory.map(vk::memory_size{ sizeof(data) }, (void**) &ptr);

	for(nuint i = 0; i < sizeof(data); ++i) *ptr++ = ((uint8*)&data)[i];

	device_memory.flush_mapped(vk::memory_size{ sizeof(data) });
	device_memory.unmap();

	vk::surface_format surface_format = physical_device.get_first_surface_format(surface);

	array color_attachments {
		vk::color_attachment_reference{ 0, vk::image_layout::color_attachment_optimal }
	};

	auto render_pass = device.create_guarded<vk::render_pass>(
		array{ vk::subpass_description {
			color_attachments
		} },
		array{ vk::subpass_dependency {
			vk::src_subpass{ VK_SUBPASS_EXTERNAL },
			vk::dst_subpass{ 0 },
			vk::src_stages{ vk::pipeline_stage::color_attachment_output },
			vk::dst_stages{ vk::pipeline_stage::color_attachment_output }
		} },
		array{ vk::attachment_description {
			surface_format.format,
			vk::load_op{ vk::attachment_load_op::clear },
			vk::store_op{ vk::attachment_store_op::store },
			vk::final_layout{ vk::image_layout::present_src_khr }
		} }
	);

	auto vertex_shader = platform::read_shader_module(device, "texture.vert.spv");
	auto fragment_shader = platform::read_shader_module(device, "texture.frag.spv");

	auto sampler = device.create_guarded<vk::sampler>(
		vk::mag_filter{ vk::filter::nearest },
		vk::min_filter{ vk::filter::nearest },
		vk::mipmap_mode::nearest,
		vk::address_mode_u{ vk::address_mode::clamp_to_edge },
		vk::address_mode_v{ vk::address_mode::clamp_to_edge },
		vk::address_mode_w{ vk::address_mode::clamp_to_edge },
		vk::mip_lod_bias{ 0.0 },
		vk::anisotropy_enable{ false },
		vk::compare_enable{ false },
		vk::compare_op::always,
		vk::min_lod{ 0.0F },
		vk::max_lod{ 0.0F },
		vk::border_color::float_transparent_black,
		vk::unnormalized_coordinates{ false }
	);

	auto descriptor_pool = device.create_guarded<vk::descriptor_pool>(
		vk::descriptor_pool_create_flags{},
		vk::max_sets{ 1 },
		array {
			vk::descriptor_pool_size {
				.type = vk::descriptor_type::combined_image_sampler,
				.descriptor_count{ 1 }
			}
		}
	);

	auto set_layout = device.create_guarded<vk::descriptor_set_layout>(
		vk::descriptor_set_layout_create_flags{},
		array {
			vk::descriptor_set_layout_binding {
				vk::descriptor_binding{ 0 },
				vk::descriptor_type::combined_image_sampler,
				vk::descriptor_count{ 1 },
				vk::shader_stages{ vk::shader_stage::fragment }
			}
		}
	);

	auto set = descriptor_pool.allocate_descriptor_set(set_layout);

	vk::descriptor_image_info descriptor_image_info {
		.sampler{ vk::get_handle(sampler) },
		.image_view{ vk::get_handle(image_view) },
		.image_layout = vk::image_layout::shader_read_only_optimal
	};

	device.update_descriptor_sets(
		array{
			vk::write_descriptor_set {
				.dst_set = vk::get_handle(set),
				.dst_binding{ 0 },
				.dst_array_element{ 0 },
				.count{ 1 },
				.descriptor_type = vk::descriptor_type::combined_image_sampler,
				.image_info = &descriptor_image_info
			}
		}
	);

	auto pipeline_layout = device.create_guarded<vk::pipeline_layout>(
		array{ vk::get_handle(set_layout) }
	);

	array dynamic_states { vk::dynamic_state::viewport, vk::dynamic_state::scissor };

	vk::pipeline_color_blend_attachment_state pcbas {
		.src_color_blend_factor = vk::blend_factor::one,
		.dst_color_blend_factor = vk::blend_factor::zero,
		.color_blend_op = vk::blend_op::add,
		.src_alpha_blend_factor = vk::blend_factor::one,
		.dst_alpha_blend_factor = vk::blend_factor::zero,
		.alpha_blend_op = vk::blend_op::add,
		.color_write_mask = { vk::color_component::r, vk::color_component::g, vk::color_component::b, vk::color_component::a }
	};

	auto pipeline = device.create_guarded<vk::pipeline>(
		pipeline_layout, render_pass,
		vk::primitive_topology::triangle_strip,
		array {
			vk::pipeline_shader_stage_create_info {
				vk::shader_stage::vertex,
				vertex_shader,
				vk::entrypoint_name{ "main" }
			},
			vk::pipeline_shader_stage_create_info {
				vk::shader_stage::fragment,
				fragment_shader,
				vk::entrypoint_name{ "main" }
			}
		},
		vk::pipeline_multisample_state_create_info{},
		vk::pipeline_vertex_input_state_create_info {
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
		vk::command_pool_create_flags{
			vk::command_pool_create_flag::reset_command_buffer,
			vk::command_pool_create_flag::transient
		}
	);

	struct rendering_resource {
		vk::guarded_handle<vk::command_buffer> command_buffer;
		vk::guarded_handle<vk::semaphore> image_acquire;
		vk::guarded_handle<vk::semaphore> finish;
		vk::guarded_handle<vk::fence> fence;
		vk::guarded_handle<vk::framebuffer> framebuffer;
	};

	array<rendering_resource, 2> rendering_resources{};

	for(auto& rr : rendering_resources) {
		rr.command_buffer = command_pool.allocate_guarded<vk::command_buffer>(vk::command_buffer_level::primary);
	}

	rendering_resources[0].command_buffer
		.begin(vk::command_buffer_usages{ vk::command_buffer_usage::one_time_submit })
		.cmd_pipeline_barrier(
			vk::src_stages{ vk::pipeline_stage::top_of_pipe },
			vk::dst_stages{ vk::pipeline_stage::transfer },
			vk::dependencies{},
			array {
				vk::image_memory_barrier {
					.dst_access{ vk::access::transfer_write },
					.old_layout{ vk::image_layout::undefined },
					.new_layout{ vk::image_layout::transfer_dst_optimal },
					.image = vk::get_handle(image),
					.subresource_range {
						vk::image_aspects{ vk::image_aspect::color }
					}
				}
			}
		)
		.cmd_copy_buffer_to_image(
			staging_buffer, image, vk::image_layout::transfer_dst_optimal,
			array{
				vk::buffer_image_copy {
					.image_subresource {
						.aspects{ vk::image_aspect::color },
						.layer_count = 1
					},
					.image_extent{
						image_info.width, image_info.height, 1
					}
				}
			}
		)
		.cmd_pipeline_barrier(
			vk::src_stages{ vk::pipeline_stage::transfer },
			vk::dst_stages{ vk::pipeline_stage::fragment_shader },
			vk::dependencies{},
			array {
				vk::image_memory_barrier {
					.src_access{ vk::access::transfer_write },
					.dst_access{ vk::access::shader_read },
					.old_layout{ vk::image_layout::transfer_dst_optimal },
					.new_layout{ vk::image_layout::shader_read_only_optimal },
					.image = vk::get_handle(image),
					.subresource_range {
						vk::image_aspects{ vk::image_aspect::color }
					}
				}
			}
		)
		.end();


	vk::guarded_handle<vk::swapchain> swapchain{};
	auto queue = device.get_queue(queue_family_index, vk::queue_index{ 0 });

	queue.submit(vk::submit_info {
		.command_buffer_count = 1,
		.command_buffers = &vk::get_handle(rendering_resources[0].command_buffer)
	});

	device.wait_idle();

	while(!platform::should_close()) {
		vk::surface_capabilities surface_capabilities = physical_device.get_surface_capabilities(surface);

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
				vk::image_subresource_range{ vk::image_aspects{ vk::image_aspect::color } }
			);
		}

		for(auto& rr : rendering_resources) {
			rr.fence = device.create_guarded<vk::fence>(vk::fence_create_flag::signaled);
			rr.image_acquire = device.create_guarded<vk::semaphore>();
			rr.finish = device.create_guarded<vk::semaphore>();
		}

		nuint rendering_resource_index = 0;

		while (!platform::should_close()) {
			auto& rr = rendering_resources[rendering_resource_index];
			
			++rendering_resource_index %= rendering_resources.size();
			
			platform::begin();

			rr.fence.wait();
			rr.fence.reset();

			auto result = swapchain.try_acquire_next_image(rr.image_acquire);
			if(result.is_unexpected()) {
				result.set_handled(true);
				if(result.get_unexpected().suboptimal() || result.get_unexpected().out_of_date()) break;
				platform::error("acquire next image").new_line();
				return;
			}

			vk::image_index image_index = result;

			rr.framebuffer = device.create_guarded<vk::framebuffer>(
				render_pass,
				array{ image_views[(uint32)image_index].handle() },
				vk::extent<3>{ surface_capabilities.current_extent.width(), surface_capabilities.current_extent.height(), 1 }
			);

			auto& command_buffer = rr.command_buffer;

			command_buffer
				.begin(vk::command_buffer_usage::one_time_submit)
				.cmd_begin_render_pass(
					render_pass, rr.framebuffer,
					vk::render_area{ surface_capabilities.current_extent },
					array{ vk::clear_value { vk::clear_color_value{ 0.0, 0.0, 0.0, 0.0 } } }
				)
				.cmd_bind_pipeline(pipeline, vk::pipeline_bind_point::graphics)
				.cmd_bind_descriptor_sets(
					vk::pipeline_bind_point::graphics,
					pipeline_layout,
					array{ vk::get_handle(set) }
				)
				.cmd_set_viewport(surface_capabilities.current_extent)
				.cmd_set_scissor(surface_capabilities.current_extent)
				.cmd_bind_vertex_buffer(buffer)
				.cmd_draw(vk::vertex_count{ 4 })
				.cmd_end_render_pass()
				.end();

			queue.submit(
				command_buffer,
				vk::wait_semaphore{ rr.image_acquire }, vk::signal_semaphore{ rr.finish },
				vk::pipeline_stages{ vk::pipeline_stage::color_attachment_output },
				rr.fence
			);

			vk::result present_result = queue.try_present(
				vk::wait_semaphore{ rr.finish },
				swapchain,
				image_index
			);

			if(!present_result.success()) {
				if(present_result.suboptimal() || present_result.out_of_date()) break;
				platform::error("present").new_line();
				return;
			}

			platform::end();
		}

		device.wait_idle();
	}
}