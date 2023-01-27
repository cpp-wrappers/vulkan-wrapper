#pragma once

#include "./get_images.hpp"

namespace vk {

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::swapchain>> == 1
	>
	vk::count get_swapchain_image_count(Args&&... args) {
		return vk::get_swapchain_images(
			span<handle<vk::image>>{ nullptr, 0 },
			forward<Args>(args)...
		);
	}

} // vk