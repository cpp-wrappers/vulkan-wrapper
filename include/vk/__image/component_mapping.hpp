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
		vk::r r{ vk::component_swizzle::identity };
		vk::g g{ vk::component_swizzle::identity };
		vk::b b{ vk::component_swizzle::identity };
		vk::a a{ vk::component_swizzle::identity };

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			count_of_decayed_same_as<vk::r> <= 1,
			count_of_decayed_same_as<vk::g> <= 1,
			count_of_decayed_same_as<vk::b> <= 1,
			count_of_decayed_same_as<vk::a> <= 1
		>
		component_mapping(Args... args) {
			if constexpr(types<Args...>::template count_of_same_as<vk::r> > 0) {
				r = tuple{ args... }.template get_same_as<vk::r>();
			}

			if constexpr(types<Args...>::template count_of_same_as<vk::g> > 0) {
				g = tuple{ args... }.template get_same_as<vk::g>();
			}

			if constexpr(types<Args...>::template count_of_same_as<vk::b> > 0) {
				b = tuple{ args... }.template get_same_as<vk::b>();
			}

			if constexpr(types<Args...>::template count_of_same_as<vk::a> > 0) {
				a = tuple{ args... }.template get_same_as<vk::a>();
			}
		}

	}; // component_mapping

} // vk