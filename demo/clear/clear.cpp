#if 0
. ./`dirname ${BASH_SOURCE[0]}`/../build.sh $@
exit 1
#endif

#include "vk/instance/guard.hpp"
#include "vk/device/guard.hpp"
#include "vk/physical_device/handle.hpp"
#include "vk/swapchain/guard.hpp"
#include "vk/command/pool/guard.hpp"
#include "vk/surface/guard.hpp"
#include "vk/semaphore/guard.hpp"
#include "vk/instance/layer_properties.hpp"

#include "../platform/platform.hpp"
#include <string.h>

int entrypoint() {
	nuint count = platform::required_instance_extension_count();
	span extensions {
		(vk::extension_name*)platform::get_required_instance_extensions(),
		platform::required_instance_extension_count()
	};

	platform::info("required extensions:\n");
	for(vk::extension_name extension_name: extensions) {
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

	vk::instance_guard instance {
		layers,
		extensions
	};

	vk::physical_device physical_device = instance.get_first_physical_device();

	vk::queue_family_index queue_family_index {
		physical_device.get_first_queue_family_index_with_capabilities(vk::queue_flag::graphics)
	};

	platform::info("graphics family index: ");
	platform::info((uint32)queue_family_index);
	platform::info('\n');

	vk::device_guard device = physical_device.create_device(
		queue_family_index,
		array { vk::queue_priority{ 1.0F } },
		array { vk::extension_name { "VK_KHR_swapchain" } }
	);

	auto surface_raw = platform::try_create_surface(instance.object());
	if(!surface_raw.is_current<vk::surface>()) {
		platform::error(surface_raw.get<c_string>().begin());
	}
	vk::surface_guard surface { surface_raw.get<vk::surface>(), instance.object()};

	if(!physical_device.get_surface_support(surface.object(), queue_family_index)) {
		platform::error("surface is not supported\n");
		return -1;
	}

	vk::surface_format surface_format = physical_device.get_first_surface_format(surface.object());

	vk::surface_capabilities surface_capabilities = physical_device.get_surface_capabilities(surface.object());

	vk::swapchain_guard swapchain {
		device.object(),
		surface.object(),
		surface_capabilities.min_image_count,
		surface_capabilities.current_extent,
		surface_format,
		vk::image_usages{ vk::image_usage::color_attachment, vk::image_usage::transfer_dst },
		vk::sharing_mode::exclusive,
		vk::present_mode::immediate,
		vk::clipped{ true },
		vk::surface_transform::identity,
		vk::composite_alpha::opaque
	};

	platform::info("created swapchain\n");

	uint32 images_count = (uint32)swapchain.get_image_count();
	vk::image images_storage[images_count];
	span<vk::image> images{ images_storage, images_count };

	swapchain.get_images(images);

	vk::command_pool_guard command_pool = device.create_guarded_command_pool(queue_family_index);

	vk::command_buffer command_buffers_storage[images_count];
	span<vk::command_buffer> command_buffers{ command_buffers_storage, images_count };

	command_pool.allocate_command_buffers(vk::command_buffer_level::primary, command_buffers);

	vk::image_subresource_range image_subresource_range { vk::image_aspect::color };

	for(int i = 0; i < images_count; ++i) {
		vk::command_buffer command_buffer = command_buffers[i];

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

	vk::semaphore_guard swapchain_image_semaphore { device.object() };
	vk::semaphore_guard rendering_finished_semaphore { device.object() };

	vk::queue presentation_queue = device.get_queue(queue_family_index, vk::queue_index{ 0 });

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

		vk::pipeline_stage wait_dst_stage_mask = vk::pipeline_stage::transfer;

		presentation_queue.submit(vk::submit_info {
			.wait_semaphore_count = 1,
			.wait_semaphores = &swapchain_image_semaphore.object(),
			.wait_dst_stage_mask = &wait_dst_stage_mask,
			.command_buffer_count = 1u,
			.command_buffers = &command_buffers[(uint32)image_index],
			.signal_semaphore_count = 1u,
			.signal_semaphores = &rendering_finished_semaphore.object()
		});

		presentation_queue.present(vk::present_info {
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