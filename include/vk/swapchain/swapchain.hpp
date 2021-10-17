#pragma once

#include <core/forward.hpp>

#include "../headers.hpp"
#include "images_view.hpp"

namespace vk {

struct device;

struct swapchain {
	swapchain() = delete;
	swapchain(const swapchain&) = delete;

	template<typename F>
	void view_images(vk::device& device, uint32_t count, F&& f) const {
		vk::view_swapchain_images(
			device,
			*this,
			count,
			forward<F>(f)
		);
	}

}; // swapchain

} // vk

