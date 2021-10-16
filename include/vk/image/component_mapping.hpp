#pragma once

#include <core/primitive_integer.hpp>
#include <core/integer.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/types/are_contain_type.hpp>
#include <core/elements/of_type.hpp>

#include "component_swizzle.hpp"

namespace vk {

struct r : uint32 {};
struct g : uint32 {};
struct b : uint32 {};
struct a : uint32 {};

struct component_mapping {
	vk::r r{ (primitive::uint32) vk::component_swizzle::identity };
	vk::g g{ (primitive::uint32) vk::component_swizzle::identity };
	vk::b b{ (primitive::uint32) vk::component_swizzle::identity };
	vk::a a{ (primitive::uint32) vk::component_swizzle::identity };

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::r>::less_or_equals<1u>,
			types::count_of_type<vk::g>::less_or_equals<1u>,
			types::count_of_type<vk::b>::less_or_equals<1u>,
			types::count_of_type<vk::a>::less_or_equals<1u>
		>::for_types_of<Args...>
	)
	component_mapping(Args... args) {
		if constexpr(types::are_contain_type<vk::r>::for_types_of<Args...>)
			r = elements::of_type<vk::r&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::g>::for_types_of<Args...>)
			g = elements::of_type<vk::g&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::b>::for_types_of<Args...>)
			b = elements::of_type<vk::b&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::a>::for_types_of<Args...>)
			a = elements::of_type<vk::a&>::for_elements_of(args...);
	};
};

}

