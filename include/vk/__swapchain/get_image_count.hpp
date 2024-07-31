#pragma once

#include "./get_images.hpp"

namespace vk {

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::swapchain>>.decayed == 1
	>
	vk::count get_swapchain_image_count(Args&&... args) {
		return vk::get_swapchain_images(
			span<handle<vk::image>>{ nullptr, 0 },
			forward<Args>(args)...
		);
	}

} // vk