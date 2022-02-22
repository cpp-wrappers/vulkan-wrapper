#pragma once

#include "handle.hpp"

#include <core/flag_enum.hpp>
#include <core/wrapper/of_integer.hpp>
#include <core/wrapper/of_pointer_to.hpp>

#include "vk/headers.hpp"
#include "vk/sharing_mode.hpp"
#include "vk/queue_family_index.hpp"
#include "vk/extent.hpp"
#include "vk/format.hpp"
#include "vk/surface/present_mode.hpp"
#include "vk/image/color_space.hpp"
#include "vk/image/usage.hpp"
#include "vk/surface/transform.hpp"
#include "vk/surface/composite_alpha.hpp"
#include "vk/surface/min_image_count.hpp"
#include "vk/surface/handle.hpp"

namespace vk {

	enum class swapchain_create_flag {
		split_instance_bind_regions = VK_SWAPCHAIN_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT_KHR,
		рrotected = VK_SWAPCHAIN_CREATE_PROTECTED_BIT_KHR,
		mutable_format = VK_SWAPCHAIN_CREATE_MUTABLE_FORMAT_BIT_KHR
	};

	struct image_array_layers : wrapper::of_integer<uint32> {};
	struct queue_family_index_count : wrapper::of_integer<uint32> {};
	struct queue_family_indices : wrapper::of_pointer_to<const vk::queue_family_index> {};
	struct clipped : wrapper::of_integer<uint32> {};

	struct swapchain_create_info {
		const uint32 type = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		const void* const next;
		flag_enum<swapchain_create_flag> flags;
		vk::handle<vk::surface> surface;
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
		vk::handle<vk::swapchain> old_swapchain;
	}; // swapchain_create_info

} // vk

static_assert(sizeof(vk::swapchain_create_info) == sizeof(VkSwapchainCreateInfoKHR));