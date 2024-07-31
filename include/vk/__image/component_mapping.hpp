#pragma once

#include "./component_swizzle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct r { vk::component_swizzle _; };
	struct g { vk::component_swizzle _; };
	struct b { vk::component_swizzle _; };
	struct a { vk::component_swizzle _; };

	struct component_mapping {
		vk::r r { vk::component_swizzle::identity };
		vk::g g { vk::component_swizzle::identity };
		vk::b b { vk::component_swizzle::identity };
		vk::a a { vk::component_swizzle::identity };

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			is_same_as<vk::r>.decayed <= 1,
			is_same_as<vk::g>.decayed <= 1,
			is_same_as<vk::b>.decayed <= 1,
			is_same_as<vk::a>.decayed <= 1
		>
		component_mapping(Args... args) {
			tuple a { args... };

			if constexpr((is_same_as<vk::r> > 0).for_types<Args...>()) {
				r = a.template get<is_same_as<vk::r>>();
			}

			if constexpr((is_same_as<vk::g> > 0).for_types<Args...>()) {
				g = tuple{ args... }.template get<is_same_as<vk::g>>();
			}

			if constexpr((is_same_as<vk::b> > 0).for_types<Args...>()) {
				b = tuple{ args... }.template get<is_same_as<vk::b>>();
			}

			if constexpr((is_same_as<vk::a> > 0).for_types<Args...>()) {
				a = tuple{ args... }.template get<is_same_as<vk::a>>();
			}
		}

	}; // component_mapping

} // vk