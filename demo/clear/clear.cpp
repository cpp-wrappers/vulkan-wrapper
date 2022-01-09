#if 0
. ./`dirname ${BASH_SOURCE[0]}`/../build.sh $@
exit 0
#endif

#include "vk/instance/guarded_handle.hpp"
#include "vk/physical_device/handle.hpp"
#include "vk/instance/layer_properties.hpp"

#include "../platform/platform.hpp"
#include <string.h>

void entrypoint() {
	vk::layer_name validation_layer_name{ "VK_LAYER_KHRONOS_validation" };
	bool validation_layer_is_supported = vk::is_instance_layer_supported(validation_layer_name);

	span<vk::layer_name> layers{ validation_layer_is_supported ? &validation_layer_name : nullptr, validation_layer_is_supported ? 1u : 0u };

	auto instance = vk::create_guarded_instance(
		layers,
		platform::get_required_instance_extensions()
	);

	auto physical_device = instance.get_first_physical_device();

	vk::queue_family_index queue_family_index {
		physical_device.get_first_queue_family_index_with_capabilities(vk::queue_flag::graphics)
	};

	platform::info("graphics family index: ", (uint32)queue_family_index).new_line();

	auto device = physical_device.create_guarded_device(
		queue_family_index,
		vk::queue_priority{ 1.0F },
		vk::extension_name { "VK_KHR_swapchain" }
	);

	auto surface = platform::create_surface(instance);

	if(!physical_device.get_surface_support(surface, queue_family_index)) {
		platform::error("surface is not supported").new_line();
		throw;
	}

	vk::surface_format surface_format = physical_device.get_first_surface_format(surface);

	vk::surface_capabilities surface_capabilities = physical_device.get_surface_capabilities(surface);

	auto swapchain = device.create_guarded<vk::swapchain>(
		surface,
		surface_capabilities.min_image_count,
		surface_capabilities.current_extent,
		surface_format,
		vk::image_usages{ vk::image_usage::color_attachment, vk::image_usage::transfer_dst },
		vk::sharing_mode::exclusive,
		vk::present_mode::immediate,
		vk::clipped{ true },
		vk::surface_transform::identity,
		vk::composite_alpha::opaque
	);

	uint32 images_count = (uint32)swapchain.get_image_count();
	vk::handle<vk::image> images_storage[images_count];
	span<vk::handle<vk::image>> images{ images_storage, images_count };

	swapchain.get_images(images);

	auto command_pool = device.create_guarded<vk::command_pool>(queue_family_index);

	vk::handle<vk::command_buffer> command_buffers_storage[images_count];
	span<vk::handle<vk::command_buffer>> command_buffers{ command_buffers_storage, images_count };

	command_pool.allocate_command_buffers(vk::command_buffer_level::primary, command_buffers);

	vk::image_subresource_range image_subresource_range { vk::image_aspect::color };

	for(nuint i = 0; i < images_count; ++i) {
		auto command_buffer = command_buffers[i];

		vk::image_memory_barrier image_memory_barrier_from_present_to_clear {
			.src_access = vk::src_access{ vk::access::memory_read },
			.dst_access = vk::dst_access{ vk::access::transfer_write },
			.old_layout = vk::old_layout{ vk::image_layout::undefined },
			.new_layout = vk::new_layout{ vk::image_layout::transfer_dst_optimal },
			.src_queue_family_index{ VK_QUEUE_FAMILY_IGNORED },
			.dst_queue_family_index{ VK_QUEUE_FAMILY_IGNORED },
			.image = images[i],
			.subresource_range = image_subresource_range
		};

		vk::image_memory_barrier image_memory_barrier_from_clear_to_present {
			.src_access = vk::src_access{ vk::access::transfer_write },
			.dst_access = vk::dst_access{ vk::access::memory_read },
			.old_layout = vk::old_layout{ vk::image_layout::transfer_dst_optimal },
			.new_layout = vk::new_layout{ vk::image_layout::present_src_khr },
			.src_queue_family_index{ VK_QUEUE_FAMILY_IGNORED },
			.dst_queue_family_index{ VK_QUEUE_FAMILY_IGNORED },
			.image = images[i],
			.subresource_range = image_subresource_range
		};

		command_buffer.begin(vk::command_buffer_usage::simultaneius_use);
		command_buffer.cmd_pipeline_barrier(
			vk::src_stage_flags { vk::pipeline_stage::transfer },
			vk::dst_stage_flags { vk::pipeline_stage::transfer },
			vk::dependency_flags{},
			array{ image_memory_barrier_from_present_to_clear }
		);
		command_buffer.cmd_clear_color_image(
			images[i],
			vk::image_layout::transfer_dst_optimal,
			vk::clear_color_value{ 1.0, 0.0, 0.0, 0.0 },
			array{ image_subresource_range }
		);
		command_buffer.cmd_pipeline_barrier(
			vk::src_stage_flags { vk::pipeline_stage::transfer },
			vk::dst_stage_flags { vk::pipeline_stage::bottom_of_pipe },
			vk::dependency_flags{},
			array{ image_memory_barrier_from_clear_to_present }
		);
		command_buffer.end();
	}

	auto swapchain_image_semaphore = device.create_guarded<vk::semaphore>();
	auto rendering_finished_semaphore = device.create_guarded<vk::semaphore>();

	auto presentation_queue = device.get_queue(queue_family_index, vk::queue_index{ 0 });

	while (!platform::should_close()) {
		platform::begin();

		auto result = swapchain.try_acquire_next_image(swapchain_image_semaphore);

		if(result.is_current<vk::result>()) {
			vk::result r = result.get<vk::result>();

			if(r.suboptimal()) break;
			platform::error("can't acquire swapchain image").new_line();
			throw;
		}

		vk::image_index image_index = result.get<vk::image_index>();

		vk::pipeline_stages wait_dst_stage_mask{ vk::pipeline_stage::transfer };

		presentation_queue.submit(vk::submit_info {
			.wait_semaphore_count = 1,
			.wait_semaphores = &swapchain_image_semaphore.handle(),
			.wait_dst_stage_mask = &wait_dst_stage_mask,
			.command_buffer_count = 1,
			.command_buffers = &command_buffers[(uint32)image_index],
			.signal_semaphore_count = 1,
			.signal_semaphores = &rendering_finished_semaphore.handle()
		});

		presentation_queue.present(vk::present_info {
			.wait_semaphore_count = 1,
			.wait_semaphores = &rendering_finished_semaphore.handle(),
			.swapchain_count = 1,
			.swapchains = &swapchain.handle(),
			.image_indices = &image_index
		});

		platform::end();
	}

	device.wait_idle();

	command_pool.free_command_buffers(command_buffers);
}