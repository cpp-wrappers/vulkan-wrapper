#pragma once

#include <core/integer.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/types/are_contain_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/wrapper/of_integer.hpp>

#include "component_swizzle.hpp"

namespace vk {

	struct r : wrapper::of<vk::component_swizzle> {};
	struct g : wrapper::of<vk::component_swizzle> {};
	struct b : wrapper::of<vk::component_swizzle> {};
	struct a : wrapper::of<vk::component_swizzle> {};

	struct component_mapping {
		vk::r r{ vk::component_swizzle::identity };
		vk::g g{ vk::component_swizzle::identity };
		vk::b b{ vk::component_swizzle::identity };
		vk::a a{ vk::component_swizzle::identity };

		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::count_of_type<vk::r>::less_or_equals<1>,
				types::count_of_type<vk::g>::less_or_equals<1>,
				types::count_of_type<vk::b>::less_or_equals<1>,
				types::count_of_type<vk::a>::less_or_equals<1>
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

