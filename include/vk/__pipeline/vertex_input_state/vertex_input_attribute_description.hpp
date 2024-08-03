#pragma once

#include <types.hpp>
#include <tuple.hpp>

#include "../../__internal/location.hpp"
#include "../../__internal/binding.hpp"
#include "../../__internal/offset.hpp"
#include "../../__internal/format.hpp"

namespace vk {

	struct vertex_input_attribute_description {
		vk::location location;
		vk::binding binding;
		vk::format format;
		vk::offset<1> offset;

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			is_same_as<vk::location> == 1,
			is_same_as<vk::binding> == 1,
			is_same_as<vk::format> == 1,
			is_same_as<vk::offset<1>> <= 1
		>
		vertex_input_attribute_description(Args... args) :
			location {
				tuple<Args...>{args...}.template get<
					is_same_as<vk::location>
				>()
			},
			binding {
				tuple<Args...>{args...}.template get<
					is_same_as<vk::binding>
				>()
			},
			format {
				tuple<Args...>{args...}.template get<
					is_same_as<vk::format>
				>()
			},
			offset {
				tuple<Args...>{args...}.template get_or<
					is_same_as<vk::offset<1>>
				>([]{ return vk::offset<1>{}; })
			}
		{}
	};

} // vk