#pragma once

#include "reset_fences.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::fence>
	>::for_types_of<Args...>
	vk::result try_reset_fence(Args&&... args) {
		return vk::try_reset_fences(
			array{ vk::handle<vk::fence>{ vk::get_handle(elements::vk::possibly_guarded_handle_of<vk::fence>::for_elements_of(args...)) }},
			elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...)
		);
	}

	template<typename... Args>
	void reset_fence(Args&&... args) {
		auto result = vk::try_reset_fence(forward<Args>(args)...);
		if(result.error()) default_unexpected_handler(result);
	}

} // vk