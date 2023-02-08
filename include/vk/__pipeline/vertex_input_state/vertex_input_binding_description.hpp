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
			count_of_decayed_same_as<vk::binding> == 1,
			count_of_decayed_same_as<vk::stride> == 1,
			count_of_decayed_same_as<vk::vertex_input_rate> <= 1
		>
		vertex_input_binding_description(Args&&... args) {
			tuple a{ args... };
			binding = a.template get_decayed_same_as<vk::binding>();
			stride = a.template get_decayed_same_as<vk::stride>();
	
			if constexpr (types<Args...>::template
				count_of_decayed_same_as<vk::vertex_input_rate> > 0
			) {
				vertex_input_rate = a.template
					get_decayed_same_as<vk::vertex_input_rate>();
			}

		} // constructor

	}; // vertex_input_binding_description

} // vk