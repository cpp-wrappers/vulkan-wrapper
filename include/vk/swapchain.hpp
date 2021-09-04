#pragma once

#include "headers.hpp"
#include "swapchain_images_view.hpp"

namespace vk {

struct device;

struct swapchain {
	swapchain() = delete;
	swapchain(const swapchain&) = delete;

	template<typename F>
	void view_images(vk::device& device, uint32_t count, F&& f) const {
		view_swapchain_images(
			(VkDevice)&device,
			(VkSwapchainKHR)this,
			std::forward<F>(f)
		);
	}

}; // swapchain

} // vk

