#pragma once

#include "../shared/destroy.hpp"
#include "handle.hpp"
#include "../device/handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::swapchain> {

		void operator () (vk::handle<vk::device> device, vk::handle<vk::swapchain> swapchain) const {
			vkDestroySwapchainKHR(
				(VkDevice) device.value,
				(VkSwapchainKHR) swapchain.value,
				nullptr
			);
		}

	};

}