#pragma once

#include "handle.hpp"
#include "../device/handle.hpp"

namespace vk {

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::count_of_ranges_of_value_type<vk::handle<vk::fence>>::equals<1>
		>::for_types_of<Args...>
	)
	vk::result try_reset_fences(Args&&... args) {
		auto& fences = elements::range_of_value_type<vk::handle<vk::fence>>::for_elements_of(args...);

		return {
			(int) vkResetFences(
				(VkDevice) vk::get_handle_value(elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...)),
				(uint32) fences.size(),
				(VkFence*) fences.data()
			)
		};
	}

	template<typename... Args>
	void reset_fences(Args&&... args) {
		auto result = vk::try_reset_fences(forward<Args>(args)...);
		if(!result.success()) throw result;
	}
}