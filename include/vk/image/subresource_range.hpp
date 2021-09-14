#pragma once

#include <core/flag_enum.hpp>
#include <core/named.hpp>
#include <core/tuple.hpp>
#include <vulkan/vulkan_core.h>
#include "aspect.hpp"

namespace vk {

struct base_mip_level : named<uint32_t> {};
struct level_count : named<uint32_t> {};
struct base_array_layer : named<uint32_t> {};
struct layer_count : named<uint32_t> {};

struct image_subresource_range {
	flag_enum<vk::image_aspect_flag> aspect_mask{};
	vk::base_mip_level base_mip_level{ 0 };
	vk::level_count level_count{ 1 };
	vk::base_array_layer base_array_layer{ 0 };
	vk::layer_count layer_count{ 1 };

	template<typename... Args>
	requires(
		types::of<Args...>::template count_of_same_as_type<vk::image_aspect_flag> >= 1 &&
		types::of<Args...>::template count_of_same_as_type<vk::base_mip_level> <= 1 &&
		types::of<Args...>::template count_of_same_as_type<vk::level_count> <= 1 &&
		types::of<Args...>::template count_of_same_as_type<vk::base_array_layer> <= 1 &&
		types::of<Args...>::template count_of_same_as_type<vk::layer_count> <= 1 &&
		types::of<Args...>::template erase_types<
			vk::image_aspect_flag, vk::base_mip_level, vk::level_count,
			vk::base_array_layer, vk::layer_count
		>::empty
	)
	image_subresource_range(Args... args) {
		tuple{ args... }
			.get([&](vk::image_aspect_flag v){ aspect_mask.set(v); })
			.get([&](vk::base_mip_level v){ base_mip_level = v; })
			.get([&](vk::level_count v){ level_count = v; })
			.get([&](vk::base_array_layer v){ base_array_layer = v; })
			.get([&](vk::layer_count v){ layer_count = v; })
		;
	}

};

}

static_assert(sizeof(vk::image_subresource_range) == sizeof(VkImageSubresourceRange));