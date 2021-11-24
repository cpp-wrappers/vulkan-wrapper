#pragma once

#include "handle.hpp"
#include "create.hpp"

namespace vk {
	class swapchain_guard {
		vk::swapchain swapchain;
		vk::device device;
	public:

		swapchain_guard(vk::swapchain swapchain, vk::device device)
			: swapchain{ swapchain }, device{ device }
		{}

		template<typename... Args>
		swapchain_guard(vk::device device, Args&&... args)
			: swapchain{ vk::create_swapchain(device, forward<Args>(args)...) }, device{ device }
		{}

		~swapchain_guard() {
			if(swapchain.handle) {
				vkDestroySwapchainKHR(
					(VkDevice) device.handle,
					(VkSwapchainKHR) exchange(swapchain.handle, 0),
					nullptr
				);
			}
		}

		const vk::swapchain& object() const {
			return swapchain;
		}

		elements::one_of<vk::result, vk::image_index>
		try_acquire_next_image(vk::timeout timeout, vk::semaphore semaphore = { VK_NULL_HANDLE }, vk::fence fence = {VK_NULL_HANDLE}) {
			return swapchain.try_acquire_next_image(device, timeout, semaphore, fence);
		}

		template<type::range_of_value_type<vk::image> Images>
		vk::count get_images(Images&& images) const {
			return swapchain.get_images(device, forward<Images>(images));
		}

		vk::count get_image_count() const {
			return swapchain.get_image_count(device);
		}

		template<typename F>
		vk::count for_each_image(F&& f) const {
			return swapchain.for_each_image(device, forward<F>(f));
		}
	};
}