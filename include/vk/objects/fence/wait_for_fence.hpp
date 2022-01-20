#pragma once

#include <core/elements/pass_satisfying_type_predicate.hpp>
#include <core/type/negated_predicate.hpp>

#include "../../type/is_possibly_guarded_handle_of.hpp"
#include "wait_for_fences.hpp"

namespace vk {
	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::fence>,
		types::count_of_type<vk::wait_all>::less_or_equals<1>,
		types::count_of_type<vk::timeout>::less_or_equals<1>
	>::for_types_of<decay<Args>...>
	vk::result try_wait_for_fence(Args&&... args) {
		auto& fence = elements::vk::possibly_guarded_handle_of<vk::fence>(args...);

		return elements::pass_satisfying_type_predicate<
			type::negated_predicate<type::vk::is_possibly_guarded_handle_of<vk::fence>>
		>(args...)(
			[&]<typename... Others>(Others&&... others) {
				return vk::try_wait_for_fences(
					array{ vk::handle<vk::fence>{ vk::get_handle(fence) } },
					forward<Others>(others)...
				);
			}
		);
	}

	template<typename... Args>
	void wait_for_fence(Args&&... args) {
		vk::result result = vk::try_wait_for_fence(forward<Args>(args)...);
		if(result.error()) default_unexpected_handler(result);
	}

} // vk