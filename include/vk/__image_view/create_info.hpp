#pragma once

#include "../__internal/format.hpp"
#include "../__image/handle.hpp"
#include "../__image/component_mapping.hpp"
#include "../__image/subresource_range.hpp"

#include <enum_flags.hpp>

namespace vk {

	enum image_view_create_flag {
		fragment_density_map_dynamic  = 0x00000001,
		fragment_density_map_deferred = 0x00000002
	};

	enum class image_view_type {
		one_d       = 0,
		two_d       = 1,
		three_d     = 2,
		cube        = 3,
		one_d_array = 4,
		two_d_array = 5,
		cube_array  = 6
	};

	struct image_view_create_info {
		uint32 structure_type = 15;
		const void* next = nullptr;
		enum_flags<image_view_create_flag> flags{};
		handle<vk::image>::underlying_type image{};
		vk::image_view_type view_type{};
		vk::format format{};
		vk::component_mapping components{};
		vk::image_subresource_range subresource_range{};
	};

} // vk