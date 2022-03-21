#pragma once

#include "wait_for_fences.hpp"

#include <core/meta/elements/pass_satisfying_type_predicate.hpp>
#include <core/meta/type/negated_predicate.hpp>

namespace vk {
	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_contain_one_possibly_guarded_handle_of<vk::fence>,
		types::are_may_contain_one_decayed<vk::wait_all>,
		types::are_may_contain_one_decayed<vk::timeout>
	>::for_types<Args...>
	vk::result try_wait_for_fence(Args&&... args) {
		auto& fence = elements::possibly_guarded_handle_of<vk::fence>(args...);

		return elements::pass_satisfying_type_predicate<
			type::negated_predicate<type::is_possibly_guarded_handle_of<vk::fence>>
		>(args...)(
			[&]<typename... Others>(Others&&... others) {
				return vk::try_wait_for_fences(
					array{ handle<vk::fence>{ vk::get_handle(fence) } },
					forward<Others>(others)...
				);
			}
		);
	}

	template<typename... Args>
	void wait_for_fence(Args&&... args) {
		vk::result result = vk::try_wait_for_fence(forward<Args>(args)...);
		if(result.error()) vk::unexpected_handler(result);
	}

} // vk