#pragma once

#include "aspect.hpp"

#include <core/flag_enum.hpp>
#include <core/integer.hpp>
#include <core/wrapper/of_integer.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>
#include <core/meta/decayed_same_as.hpp>

namespace vk {

	struct base_mip_level : wrapper::of_integer<uint32> {};
	struct level_count : wrapper::of_integer<uint32> {};
	struct base_array_layer : wrapper::of_integer<uint32> {};
	struct layer_count : wrapper::of_integer<uint32> {};
	
	struct image_subresource_range {
		vk::image_aspects aspect_mask{};
		vk::base_mip_level base_mip_level{ 0 };
		vk::level_count level_count{ 1 };
		vk::base_array_layer base_array_layer{ 0 };
		vk::layer_count layer_count{ 1 };
	
		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::are_contain_one_decayed_same_as<vk::image_aspects>,
			types::are_may_contain_one_decayed_same_as<vk::base_mip_level>,
			types::are_may_contain_one_decayed_same_as<vk::level_count>,
			types::are_may_contain_one_decayed_same_as<vk::base_array_layer>,
			types::are_may_contain_one_decayed_same_as<vk::layer_count>
		>::for_types<Args...>
		image_subresource_range(Args... args) {
			aspect_mask = elements::decayed_same_as<vk::image_aspects>(args...);
	
			if constexpr(types::are_contain_decayed_same_as<vk::base_mip_level>::for_types<Args...>) {
				base_mip_level = elements::decayed_same_as<vk::base_mip_level>(args...);
			}
	
			if constexpr(types::are_contain_decayed_same_as<vk::level_count>::for_types<Args...>) {
				level_count = elements::decayed_same_as<vk::level_count>(args...);
			}
	
			if constexpr(types::are_contain_decayed_same_as<vk::base_array_layer>::for_types<Args...>) {
				base_array_layer = elements::decayed_same_as<vk::base_array_layer>(args...);
			}
	
			if constexpr(types::are_contain_decayed_same_as<vk::layer_count>::for_types<Args...>) {
				layer_count = elements::decayed_same_as<vk::layer_count>(args...);
			}
		}
	
	};

} // vk

static_assert(sizeof(vk::image_subresource_range) == sizeof(VkImageSubresourceRange));