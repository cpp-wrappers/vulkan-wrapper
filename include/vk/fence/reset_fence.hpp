#pragma once

#include "reset_fences.hpp"

#include "vk/unexpected_handler.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_contain_one_possibly_guarded_handle_of<vk::fence>
	>::for_types<Args...>
	vk::result try_reset_fence(Args&&... args) {
		return vk::try_reset_fences(
			array{ handle<vk::fence>{ vk::get_handle(elements::possibly_guarded_handle_of<vk::fence>(args...)) }},
			elements::possibly_guarded_handle_of<vk::device>(args...)
		);
	}

	template<typename... Args>
	void reset_fence(Args&&... args) {
		auto result = vk::try_reset_fence(forward<Args>(args)...);
		if(result.error()) vk::unexpected_handler(result);
	}

} // vk