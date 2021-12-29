#pragma once

#include "reset_fences.hpp"

namespace vk {

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::vk::contain_one<vk::device>,
			types::vk::contain_one<vk::fence>
		>::for_types_of<Args...>
	)
	vk::result try_reset_fence(Args&&... args) {
		return vk::try_reset_fences(
			array{ vk::handle<vk::fence>{ vk::get_handle(elements::vk::of_type<vk::fence>::for_elements_of(args...)) }},
			elements::vk::of_type<vk::device>::for_elements_of(args...)
		);
	}

	template<typename... Args>
	void reset_fence(Args&&... args) {
		auto result = vk::try_reset_fence(forward<Args>(args)...);
		if(!result.success()) throw result;
	}

}