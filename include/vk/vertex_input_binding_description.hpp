#pragma once

#include <cinttypes>
#include <core/named.hpp>
#include <core/tuple.hpp>
#include "binding.hpp"

namespace vk {

struct stride : named<uint32_t>{};

enum class vertex_input_rate {
	vertex, instance
};

struct vertex_input_binding_description {
	vk::binding binding;
	vk::stride stride;
	vk::vertex_input_rate vertex_input_rate{ vertex_input_rate::vertex };

	template<typename... Args>
	requires(
		types::of<Args...>::template count_of_same_as_type<vk::binding> == 1 &&
		types::of<Args...>::template count_of_same_as_type<vk::stride> == 1 &&
		types::of<Args...>::template count_of_same_as_type<vk::vertex_input_rate> <= 1 &&
		types::of<Args...>::template erase_types<
			vk::binding, vk::stride, vk::vertex_input_rate
		>::empty
	)
	vertex_input_binding_description(Args... args) {
		tuple{ args... }
			.get([&](vk::binding v){ binding = v; })
			.get([&](vk::stride v){ stride = v; })
			.get([&](vk::vertex_input_rate v){ vertex_input_rate = v; })
		;
	}
};

}