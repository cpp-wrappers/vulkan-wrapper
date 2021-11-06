#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/types/are_contain_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/wrapper/of_integer.hpp>

#include "../../shared/binding.hpp"

namespace vk {

	struct stride : wrapper::of_integer<uint32> {};
	
	enum class vertex_input_rate {
		vertex, instance
	};
	
	struct vertex_input_binding_description {
		vk::binding binding;
		vk::stride stride;
		vk::vertex_input_rate vertex_input_rate{ vertex_input_rate::vertex };
	
		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::count_of_type<vk::binding>::equals<1u>,
				types::count_of_type<vk::stride>::equals<1u>,
				types::count_of_type<vk::vertex_input_rate>::less_or_equals<1u>
			>::for_types_of<Args...>
		)
		vertex_input_binding_description(Args... args) {
			binding = elements::of_type<vk::binding&>::for_elements_of(args...);
			stride = elements::of_type<vk::stride&>::for_elements_of(args...);
	
			if constexpr(types::are_contain_type<vk::vertex_input_rate>::for_types_of<Args...>) {
				vertex_input_rate = elements::of_type<vk::vertex_input_rate&>::for_elements_of(args...);
			}
		}
	};

}