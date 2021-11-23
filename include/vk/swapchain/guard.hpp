#pragma once

#include "handle.hpp"

namespace vk {
	class swapchain_guard {
		vk::swapchain swapchain;
		vk::device device;
	public:

		swapchain_guard(vk::swapchain swapchain, vk::device device)
			: swapchain{ swapchain }, device{ device }
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
	};
}