#pragma once

#include <core/named.hpp>
#include <core/tuple.hpp>
#include "component_swizzle.hpp"

namespace vk {

struct r : named<vk::component_swizzle> {};
struct g : named<vk::component_swizzle> {};
struct b : named<vk::component_swizzle> {};
struct a : named<vk::component_swizzle> {};

struct component_mapping {
	vk::r r{ vk::component_swizzle::identity };
	vk::g g{ vk::component_swizzle::identity };
	vk::b b{ vk::component_swizzle::identity };
	vk::a a{ vk::component_swizzle::identity };

	template<typename... Args>
	requires(
		types::of<Args...>::template count_of_same_as_type<vk::r> <= 1 &&
		types::of<Args...>::template count_of_same_as_type<vk::g> <= 1 &&
		types::of<Args...>::template count_of_same_as_type<vk::b> <= 1 &&
		types::of<Args...>::template count_of_same_as_type<vk::a> <= 1 &&
		types::of<Args...>::template erase_types<
			vk::r, vk::g, vk::b, vk::a
		>::empty
	)
	component_mapping(Args... args) {
		tuple{ args... }
			.get([&](vk::r v){ r = v; })
			.get([&](vk::g v){ g = v; })
			.get([&](vk::b v){ b = v; })
			.get([&](vk::a v){ a = v; })
		;
	};
};

}

