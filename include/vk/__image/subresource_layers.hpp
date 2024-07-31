#pragma once

#include <types.hpp>
#include <tuple.hpp>

#include "aspect.hpp"
#include "./layer.hpp"

namespace vk {

	struct mip_level { uint32 _; };

	struct image_subresource_layers {
		vk::image_aspects aspects{ vk::image_aspect::color };
		vk::mip_level mip_level{ 0 };
		vk::base_array_layer base_array_layer{ 0 };
		vk::layer_count layer_count{ 1 };

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			is_same_as<vk::image_aspects> <= 1,
			is_same_as<vk::mip_level> <= 1,
			is_same_as<vk::base_array_layer> <= 1,
			is_same_as<vk::layer_count> <= 1
		>
		image_subresource_layers(Args... args) {
			tuple<Args...> a{args...};

			if constexpr (
				(is_same_as<vk::image_aspects> > 0).for_types<Args...>()
			) {
				aspects = a.template get<is_same_as<vk::image_aspects>>();
			}

			if constexpr (
				(is_same_as<vk::mip_level> > 0).for_types<Args...>()
			) {
				mip_level = a.template get<is_same_as<vk::mip_level>>();
			}

			if constexpr (
				(is_same_as<vk::base_array_layer> > 0).for_types<Args...>()
			) {
				mip_level = a.template get<is_same_as<vk::base_array_layer>>();
			}

			if constexpr (
				(is_same_as<vk::layer_count> > 0).for_types<Args...>()
			) {
				mip_level = a.template get<is_same_as<vk::layer_count>>();
			}
		}
	};

} // vk