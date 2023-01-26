#pragma once

#include "./aspect.hpp"

#include <types.hpp>
#include <tuple.hpp>

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
		requires types<Args...>::template exclusively_satisfy_predicates<
			count_of_decayed_same_as<vk::image_aspects> <= 1,
			count_of_decayed_same_as<vk::base_mip_level> <= 1,
			count_of_decayed_same_as<vk::level_count> <= 1,
			count_of_decayed_same_as<vk::base_array_layer> <= 1,
			count_of_decayed_same_as<vk::layer_count> <= 1
		>
		image_subresource_range(Args&&... args) {
			tuple a { args... };
			if constexpr (types<Args...>::template
				count_of_decayed_same_as<vk::image_aspects> > 0
			) {
				aspect_mask = a.template
					get_decayed_same_as<vk::image_aspects>();
			}
	
			if constexpr (types<Args...>::template
				count_of_decayed_same_as<vk::base_mip_level> > 0
			) {
				base_mip_level = a.template
					get_decayed_same_as<vk::base_mip_level>();
			}
	
			if constexpr (types<Args...>::template
				count_of_decayed_same_as<vk::level_count> > 0
			) {
				level_count = a.template
					get_decayed_same_as<vk::level_count>();
			}
	
			if constexpr (types<Args...>::template
				count_of_decayed_same_as<vk::base_array_layer> > 0
			) {
				base_array_layer = a.template
					get_decayed_same_as<vk::base_array_layer>();
			}
	
			if constexpr (types<Args...>::template
				count_of_decayed_same_as<vk::layer_count> > 0
			) {
				layer_count = a.template
					get_decayed_same_as<vk::layer_count>();
			}

		} // constructor
	
	}; // image_subresource_range

} // vk