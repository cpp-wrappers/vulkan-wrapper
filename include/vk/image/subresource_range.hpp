#pragma once

#include "aspect.hpp"

#include <core/flag_enum.hpp>
#include <core/integer.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/meta/decayed_same_as.hpp>

namespace vk {

	struct base_mip_level { uint32 _; };
	struct level_count { uint32 _; };
	struct base_array_layer { uint32 _; };
	struct layer_count { uint32 _; };
	
	struct image_subresource_range {
		vk::image_aspects aspect_mask{ vk::image_aspect::color };
		vk::base_mip_level base_mip_level{ 0 };
		vk::level_count level_count{ 1 };
		vk::base_array_layer base_array_layer{ 0 };
		vk::layer_count layer_count{ 1 };
	
		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_may_contain_one_decayed<vk::image_aspects>,
			types::are_may_contain_one_decayed<vk::base_mip_level>,
			types::are_may_contain_one_decayed<vk::level_count>,
			types::are_may_contain_one_decayed<vk::base_array_layer>,
			types::are_may_contain_one_decayed<vk::layer_count>
		>::for_types<Args...>
		image_subresource_range(Args... args) {
			if constexpr (
				types::are_contain_decayed<
					vk::image_aspects
				>::for_types<Args...>
			) { aspect_mask = elements::decayed<vk::image_aspects>(args...); }
	
			if constexpr (
				types::are_contain_decayed<
					vk::base_mip_level
				>::for_types<Args...>
			) {
				base_mip_level = elements::decayed<vk::base_mip_level>(args...);
			}
	
			if constexpr (
				types::are_contain_decayed<vk::level_count>::for_types<Args...>
			) { level_count = elements::decayed<vk::level_count>(args...); }
	
			if constexpr (
				types::are_contain_decayed<
					vk::base_array_layer
				>::for_types<Args...>
			) {
				base_array_layer = {
					elements::decayed<vk::base_array_layer>(args...)
				};
			}
	
			if constexpr (
				types::are_contain_decayed<vk::layer_count>::for_types<Args...>
			) { layer_count = elements::decayed<vk::layer_count>(args...); }

		} // constructor
	
	}; // image_subresource_range

} // vk