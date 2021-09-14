#pragma once

#include <core/integer.hpp>
#include <core/flag_enum.hpp>
#include <core/named.hpp>
#include "../headers.hpp"
#include "format.hpp"
#include "component_mapping.hpp"
#include "subresource_range.hpp"

namespace vk {

enum image_view_create_flag {
	fragment_density_map_dynamic = VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DYNAMIC_BIT_EXT,
	fragment_density_map_deferred = VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DEFERRED_BIT_EXT
};

enum class image_view_type {
	one_d = VK_IMAGE_VIEW_TYPE_1D,
	two_d = VK_IMAGE_VIEW_TYPE_2D,
	three_d = VK_IMAGE_VIEW_TYPE_3D,
	cube = VK_IMAGE_VIEW_TYPE_CUBE,
	one_d_array = VK_IMAGE_VIEW_TYPE_1D_ARRAY,
	two_d_array = VK_IMAGE_VIEW_TYPE_2D_ARRAY,
	cube_array = VK_IMAGE_VIEW_TYPE_CUBE_ARRAY
};

struct image;

struct image_view_create_info {
	uint_with_size_of<VkStructureType> type = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	const void* next = nullptr;
	flag_enum<image_view_create_flag> flags{};
	vk::image& image;
	vk::image_view_type view_type;
	vk::format format;
	vk::component_mapping components;
	vk::image_subresource_range subresource_range;
};

}

static_assert(sizeof(vk::image_view_create_info) == sizeof(VkImageViewCreateInfo));