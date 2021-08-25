#pragma once

#include "headers.hpp"

namespace vk {

struct swapchain {

	VkSwapchainKHR m_swapchain;

	template<typename... Ps>
	swapchain(const Ps&...);
};

} // vk

#include "swapchain_create_info.hpp"

