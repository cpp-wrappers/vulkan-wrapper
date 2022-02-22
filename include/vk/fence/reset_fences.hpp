#pragma once

#include "handle.hpp"

#include "vk/device/handle.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::count_of_ranges_of_value_type<vk::handle<vk::fence>>::equals<1>
	>::for_types<Args...>
	vk::result try_reset_fences(Args&&... args) {
		auto& fences = elements::range_of_value_type<vk::handle<vk::fence>>(args...);

		return {
			(int) vkResetFences(
				(VkDevice) vk::get_handle_value(elements::vk::possibly_guarded_handle_of<vk::device>(args...)),
				(uint32) fences.size(),
				(VkFence*) fences.data()
			)
		};
	}

	template<typename... Args>
	void reset_fences(Args&&... args) {
		auto result = vk::try_reset_fences(forward<Args>(args)...);
		if(result.error()) vk::default_unexpected_handler(result);
	}

} // vk