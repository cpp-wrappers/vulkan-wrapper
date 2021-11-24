#if 0
pushd `dirname $0`
bash build_and_run.sh clear "-lglfw"
popd
exit 1
#endif

#include "vk/instance/guard.hpp"
#include "vk/device/guard.hpp"
#include "vk/physical_device/handle.hpp"
#include "vk/surface/guard.hpp"
#include "vk/swapchain/guard.hpp"
#include "vk/command/pool/guard.hpp"
#include "vk/semaphore/guard.hpp"

#include <GLFW/glfw3.h>
#include <stdio.h>

int main() {
	if (!glfwInit()) {
		fprintf(stderr, "glfw init failed\n");
		return -1;
	}

	if(glfwVulkanSupported()) {
		printf("supported\n");
	}
	else {
		fprintf(stderr, "vulkan isn't supported\n");
		return -1;
	}

	uint32 count;
	const char** extensions_raw = glfwGetRequiredInstanceExtensions(&count);
	span extensions{ (vk::extension_name*)extensions_raw, count};

	printf("required extensions:\n");
	for(auto ex_name: extensions)
		printf("%s\n", ex_name.begin());
	fflush(stdout);

	vk::instance_guard instance {
		array { vk::layer_name{ "VK_LAYER_KHRONOS_validation" } },
		extensions
	};

	float ps[1]{ 1.0F };

	vk::physical_device physical_device = instance.get_first_physical_device();

	vk::queue_family_index queue_family_index {
		physical_device.first_queue_family_index_with_capabilities(vk::queue_flag::graphics)
	};

	printf("graphics family index: %d\n", (uint32)queue_family_index);

	vk::device_guard device {
		physical_device,
		array {
			vk::queue_create_info {
				queue_family_index,
				vk::queue_count{ 1 },
				vk::queue_priorities{ ps }
			}
		},
		array {
			vk::extension_name {
				"VK_KHR_swapchain"
			}
		}
	};

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* window;
	window = glfwCreateWindow(640, 480, "Vulkan Clear", nullptr, nullptr);
	if (!window) {
		fprintf(stderr, "window creation failed\n");
		return -1;
	}

	vk::surface surface_raw;

	if(glfwCreateWindowSurface(
		(VkInstance) instance.object().handle,
		window,
		nullptr,
		(VkSurfaceKHR*) &surface_raw.handle
	) >= 0) {
		printf("created surface\n");
	}
	else {
		fprintf(stderr, "surface creation failed\n");
		return -1;
	}

	vk::surface_guard surface{ surface_raw, instance.object() };

	if(!physical_device.get_surface_support(surface.object(), queue_family_index)) {
		fprintf(stderr, "surface is not supported by queue family\n");
		return -1;
	}

	vk::surface_format first_surface_format;

	physical_device.view_surface_formats(surface.object(), [&](auto formats) {
		first_surface_format = formats[0];
	});

	vk::surface_capabilities surface_capabilities = physical_device.get_surface_capabilities(surface.object());

	vk::swapchain_guard swapchain {
		device.object(),
		surface.object(),
		vk::min_image_count{ surface_capabilities.min_image_count },
		first_surface_format.format,
		first_surface_format.color_space,
		surface_capabilities.current_extent,
		vk::image_usage::color_attachment,
		vk::image_usage::transfer_dst,
		vk::sharing_mode::exclusive,
		vk::queue_family_index_count{ 0 },
		vk::queue_family_indices{ nullptr },
		vk::present_mode::immediate,
		vk::clipped{ 1 },
		vk::surface_transform::identity,
		vk::composite_alpha::opaque
	};

	printf("created swapchain\n");

	uint32 images_count = (uint32)swapchain.get_image_count();
	vk::image images_storage[images_count];
	span<vk::image> images{ images_storage, images_count };

	swapchain.get_images(images);

	vk::command_pool_guard command_pool {
		device.object(),
		queue_family_index
	};

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

	vk::queue presentation_queue = device.get_queue(queue_family_index, vk::queue_index{ 0u });

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		auto result = swapchain.try_acquire_next_image(vk::timeout{ UINT64_MAX }, swapchain_image_semaphore.object());

		if(result.is_current<vk::result>()) {
			vk::result r = result.get<vk::result>();

			if((uint32)r == VK_SUBOPTIMAL_KHR) break;
			fprintf(stderr, "can't acquire swapchain image\n");
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
	}
}