#pragma once

#include "handle.hpp"
#include "view_images.hpp"

namespace vk {

	template<typename Handler>
	void for_each_swapchain_image(
		handle<vk::device> device,
		handle<vk::swapchain> swapchain,
		vk::count count,
		Handler&& handler
	) {
		vk::view_swapchain_images(device, swapchain, count, [&](auto view) {
			for(handle<vk::image> image : view) {
				handler(image);
			}
		});
	}

	template<typename Handler>
	void for_each_swapchain_image(
		handle<vk::device> device,
		handle<vk::swapchain> swapchain,
		Handler&& handler
	) {
		vk::for_each_swapchain_image(
			device,
			swapchain,
			vk::get_swapchain_image_count(device, swapchain),
			forward<Handler>(handler)
		);
	}

} // vk

template<typename Handler>
void handle<vk::device>::for_each_swapchain_image(
	handle<vk::swapchain> swapchain, Handler&& handler
) const {
	vk::for_each_swapchain_image(*this, swapchain, forward<Handler>(handler));
}