#pragma once

#include "component_swizzle.hpp"
#include <core/wrapper/of_integer.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

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
				types::are_may_contain_one_decayed_same_as<vk::r>,
				types::are_may_contain_one_decayed_same_as<vk::g>,
				types::are_may_contain_one_decayed_same_as<vk::b>,
				types::are_may_contain_one_decayed_same_as<vk::a>
			>::for_types<Args...>
		)
		component_mapping(Args... args) {
			if constexpr(types::are_contain_decayed_same_as<vk::r>::for_types<Args...>)
				r = elements::decayed_same_as<vk::r>(args...);

			if constexpr(types::are_contain_decayed_same_as<vk::g>::for_types<Args...>)
				g = elements::decayed_same_as<vk::g>(args...);

			if constexpr(types::are_contain_decayed_same_as<vk::b>::for_types<Args...>)
				b = elements::decayed_same_as<vk::b>(args...);

			if constexpr(types::are_contain_decayed_same_as<vk::a>::for_types<Args...>)
				a = elements::decayed_same_as<vk::a>(args...);
		}

	};

} // vk