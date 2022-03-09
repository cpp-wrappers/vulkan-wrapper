#pragma once

#include <core/wrapper/of_integer.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

#include "vk/binding.hpp"

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
		requires types::are_exclusively_satsify_predicates<
			types::are_contain_one_decayed<vk::binding>,
			types::are_contain_one_decayed<vk::stride>,
			types::are_may_contain_one_decayed<vk::vertex_input_rate>
		>::for_types<Args...>
		vertex_input_binding_description(Args&&... args) {
			binding = elements::decayed<vk::binding>(args...);
			stride = elements::decayed<vk::stride>(args...);
	
			if constexpr(types::are_contain_decayed<vk::vertex_input_rate>::for_types<Args...>) {
				vertex_input_rate = elements::decayed<vk::vertex_input_rate>(args...);
			}
		}
	};

} // vk