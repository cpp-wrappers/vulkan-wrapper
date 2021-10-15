#pragma once

#include <core/flag_enum.hpp>
#include <core/integer.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/are_contain_type.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/for_each_of_type.hpp>

#include "aspect.hpp"

namespace vk {

struct base_mip_level : uint32 {};
struct level_count : uint32 {};
struct base_array_layer : uint32 {};
struct layer_count : uint32 {};

struct image_subresource_range {
	flag_enum<vk::image_aspect_flag> aspect_mask{};
	vk::base_mip_level base_mip_level{ 0u };
	vk::level_count level_count{ 1u };
	vk::base_array_layer base_array_layer{ 0u };
	vk::layer_count layer_count{ 1u };

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::image_aspect_flag>::greater_or_equals<1u>,
			types::count_of_type<vk::base_mip_level>::less_or_equals<1u>,
			types::count_of_type<vk::level_count>::less_or_equals<1u>,
			types::count_of_type<vk::base_array_layer>::less_or_equals<1u>,
			types::count_of_type<vk::layer_count>::less_or_equals<1u>
		>::for_types_of<Args...>
	)
	image_subresource_range(Args... args) {
		elements::for_each_of_type_remove_reference<vk::image_aspect_flag>(
			[&](auto af) { aspect_mask.set(af); },
			args...
		);

		if constexpr(types::are_contain_type<vk::base_mip_level>::for_types_of<Args...>) {
			base_mip_level = elements::of_type<vk::base_mip_level&>::for_elements_of(args...);
		}

		if constexpr(types::are_contain_type<vk::level_count>::for_types_of<Args...>) {
			level_count = elements::of_type<vk::level_count&>::for_elements_of(args...);
		}

		if constexpr(types::are_contain_type<vk::base_array_layer>::for_types_of<Args...>) {
			base_array_layer = elements::of_type<vk::base_array_layer&>::for_elements_of(args...);
		}

		if constexpr(types::are_contain_type<vk::layer_count>::for_types_of<Args...>) {
			layer_count = elements::of_type<vk::layer_count&>::for_elements_of(args...);
		}
	}

};

}

static_assert(sizeof(vk::image_subresource_range) == sizeof(VkImageSubresourceRange));