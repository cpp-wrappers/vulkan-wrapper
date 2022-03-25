#pragma once

#include "handle.hpp"

#include "../sharing_mode.hpp"
#include "../queue_family_index.hpp"
#include "../extent.hpp"
#include "../format.hpp"
#include "../surface/present_mode.hpp"
#include "../image/color_space.hpp"
#include "../image/usage.hpp"
#include "../surface/transform.hpp"
#include "../surface/composite_alpha.hpp"
#include "../surface/min_image_count.hpp"
#include "../surface/handle.hpp"

#include <core/flag_enum.hpp>
#include <core/wrapper/of_integer.hpp>
#include <core/wrapper/of_pointer_to.hpp>

namespace vk {

	enum class swapchain_create_flag {
		split_instance_bind_regions = 0x00000001,
		_protected                  = 0x00000002,
		mutable_format              = 0x00000004
	};

	struct image_array_layers : wrapper::of_integer<uint32> {};
	struct queue_family_index_count : wrapper::of_integer<uint32> {};
	struct queue_family_indices :
		wrapper::of_pointer_to<const vk::queue_family_index>
	{};

	struct clipped : wrapper::of_integer<uint32> {};

	struct swapchain_create_info {
		uint32 structure_type = 1000001000;
		const void* next = nullptr;
		flag_enum<swapchain_create_flag> flags;
		handle<vk::surface> surface;
		vk::min_image_count min_image_count;
		vk::format format;
		vk::color_space color_space;
		vk::extent<2> extent;
		vk::image_array_layers image_array_layers{ 1 };
		vk::image_usages usage;
		vk::sharing_mode sharing_mode;
		vk::queue_family_index_count queue_family_index_count;
		vk::queue_family_indices queue_family_indices;
		flag_enum<vk::surface_transform> pre_transform;
		flag_enum<vk::composite_alpha> composite_alpha;
		vk::present_mode present_mode;
		vk::clipped clipped;
		handle<vk::swapchain> old_swapchain{};
	};

} // vk