#pragma once

#include <types.hpp>
#include <tuple.hpp>

#include "./aspect.hpp"
#include "./layer.hpp"

namespace vk {

	struct base_mip_level { uint32 _; };
	struct level_count { uint32 _; };
	
	struct image_subresource_range {
		vk::image_aspects aspect_mask { vk::image_aspect::color };
		vk::base_mip_level base_mip_level { 0 };
		vk::level_count level_count { 1 };
		vk::base_array_layer base_array_layer { 0 };
		vk::layer_count layer_count { 1 };
	
		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			is_same_as<vk::image_aspects>.decayed <= 1,
			is_same_as<vk::base_mip_level>.decayed <= 1,
			is_same_as<vk::level_count>.decayed <= 1,
			is_same_as<vk::base_array_layer>.decayed <= 1,
			is_same_as<vk::layer_count>.decayed <= 1
		>
		image_subresource_range(Args&&... args) {
			tuple a { args... };
			if constexpr (
				(is_same_as<vk::image_aspects>.decayed > 0)
				.for_types<Args...>()
			) {
				aspect_mask = a.template
					get<is_same_as<vk::image_aspects>.decayed>();
			}
	
			if constexpr (
				(is_same_as<vk::base_mip_level>.decayed > 0)
				.for_types<Args...>()
			) {
				base_mip_level = a.template
					get<is_same_as<vk::base_mip_level>.decayed>();
			}
	
			if constexpr (
				(is_same_as<vk::level_count>.decayed > 0)
				.for_types<Args...>()
			) {
				level_count = a.template
					get<is_same_as<vk::level_count>.decayed>();
			}
	
			if constexpr (
				(is_same_as<vk::base_array_layer> > 0)
				.for_types<Args...>()
			) {
				base_array_layer = a.template
					get<is_same_as<vk::base_array_layer>.decayed>();
			}
	
			if constexpr (
				(is_same_as<vk::layer_count> > 0)
				.for_types<Args...>()
			) {
				layer_count = a.template
					get<is_same_as<vk::layer_count>.decayed>();
			}

		} // constructor
	
	}; // image_subresource_range

} // vk