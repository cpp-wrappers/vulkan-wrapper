#pragma once

#include "handle.hpp"
#include "view_images.hpp"

namespace vk {

	void for_each_swapchain_image(
		handle<vk::device> device,
		handle<vk::swapchain> swapchain,
		vk::count count, auto&& f
	) {
		vk::view_swapchain_images(device, swapchain, count, [&](auto view) {
			for(handle<vk::image> image : view) {
				f(image);
			}
		});
	}

	template<typename F>
	void for_each_swapchain_image(
		handle<vk::device> device,
		handle<vk::swapchain> swapchain,
		F&& f
	) {
		auto count = vk::get_swapchain_image_count(device, swapchain);
		vk::for_each_swapchain_image(device, count, forward<F>(f));
	}

} // vk

template<typename F>
void
handle<vk::device>::for_each_swapchain_image(
	handle<vk::swapchain> swapchain, F&& f
) const {
	vk::for_each_swapchain_image(*this, swapchain, forward<F>(f));
}