#pragma once

#include "../../__internal/binding.hpp"
#include "../../__internal/stride.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {
	
	enum class vertex_input_rate {
		vertex   = 0,
		instance = 1
	};
	
	struct vertex_input_binding_description {
		vk::binding binding;
		vk::stride stride;
		vk::vertex_input_rate vertex_input_rate{ vertex_input_rate::vertex };
	
		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			is_same_as<vk::binding>.decayed == 1,
			is_same_as<vk::stride>.decayed == 1,
			is_same_as<vk::vertex_input_rate>.decayed <= 1
		>
		vertex_input_binding_description(Args&&... args) {
			tuple a{ args... };
			binding = a.template get<is_same_as<vk::binding>.decayed>();
			stride = a.template get<is_same_as<vk::stride>.decayed>();
	
			if constexpr (
				(is_same_as<vk::vertex_input_rate>.decayed > 0)
				.for_types<Args...>()
			) {
				vertex_input_rate = a.template
					get<is_same_as<vk::vertex_input_rate>.decayed>();
			}

		} // constructor

	}; // vertex_input_binding_description

} // vk