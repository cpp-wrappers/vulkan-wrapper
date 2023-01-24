#pragma once

#include "get_images.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::device>>,
		types::are_contain_one_decayed<handle<vk::swapchain>>
	>::for_types<Args...>
	vk::count get_swapchain_image_count(Args&&... args) {
		return vk::get_swapchain_images(
			span<handle<vk::image>>{ nullptr, 0 },
			forward<Args>(args)...
		);
	}

} // vk

vk::count inline
handle<vk::device>::get_swapchain_image_count(
	handle<vk::swapchain> swapchain
) const {
	return vk::get_swapchain_image_count(*this, swapchain);
}