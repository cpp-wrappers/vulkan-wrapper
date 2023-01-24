#pragma once

#include "handle.hpp"
#include "get_images.hpp"
#include "get_image_count.hpp"

#include "../device/handle.hpp"

namespace vk {

	decltype(auto)
	view_swapchain_images(
		handle<vk::device> device,
		handle<vk::swapchain> swapchain,
		vk::count count,
		auto&& f
	) {
		handle<vk::image> images[(uint32)count];
		count = vk::get_swapchain_images(
			device,
			swapchain,
			span{ images, (uint32)count }
		);
		return f(span{ images, (uint32)count });
	}

	template<typename F>
	decltype(auto)
	view_images(
		handle<vk::device> device,
		handle<vk::swapchain> swapchain,
		F&& f
	) {
		auto count = vk::get_swapchain_image_count(device, swapchain);
		return vk::view_swapchain_images(
			device, swapchain, count, forward<F>(f)
		);
	}

} // vk

