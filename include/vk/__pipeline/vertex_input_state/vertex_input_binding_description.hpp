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
			is_same_as<vk::binding> == 1,
			is_same_as<vk::stride> == 1,
			is_same_as<vk::vertex_input_rate> <= 1
		>
		vertex_input_binding_description(Args... args) :
			binding {
				tuple<Args...>{ args... }
				.template get<is_same_as<vk::binding>>()
			},
			stride {
				tuple<Args...>{ args... }
				.template get<is_same_as<vk::stride>>()
			},
			vertex_input_rate {
				tuple<Args...>{ args... }.template get_or<
					is_same_as<vk::vertex_input_rate>
				>([]{ return vertex_input_rate::vertex; })
			}
		{}

	}; // vertex_input_binding_description

} // vk