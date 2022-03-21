#pragma once

#include "handle.hpp"

#include "vk/device/handle.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_contain_one_range_of<handle<vk::fence>>
	>::for_types<Args...>
	vk::result try_reset_fences(Args&&... args) {
		auto& fences = elements::range_of<handle<vk::fence>>(args...);

		return {
			(int) vkResetFences(
				(VkDevice) vk::get_handle_value(elements::possibly_guarded_handle_of<vk::device>(args...)),
				(uint32) fences.size(),
				(VkFence*) fences.data()
			)
		};
	}

	template<typename... Args>
	void reset_fences(Args&&... args) {
		auto result = vk::try_reset_fences(forward<Args>(args)...);
		if(result.error()) vk::unexpected_handler(result);
	}

} // vk