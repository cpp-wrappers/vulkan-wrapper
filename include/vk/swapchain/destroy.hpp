#pragma once

#include "handle.hpp"

#include "../function.hpp"
#include "../destroy_or_free.hpp"
#include "../device_child_destroy_base.hpp"
#include "../device/handle.hpp"

extern "C" VK_ATTR void VK_CALL vkDestroySwapchainKHR(
	handle<vk::device> device,
	handle<vk::swapchain> swapchain,
	const void* allocator
);

namespace vk {

	template<>
	struct vk::destroy_t<vk::swapchain> :
		vk::device_child_destroy_base<
			vk::swapchain,
			vkDestroySwapchainKHR
		>
	{};

} // vk