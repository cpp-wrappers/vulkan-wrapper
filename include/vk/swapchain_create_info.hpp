#pragma once

#include "headers.hpp"
#include <cstdint>
#include <cxx_util/int_with_size.hpp>
#include <cxx_util/bitmask_from_enum.hpp>
#include <vulkan/vulkan_core.h>
#include "surface.hpp"
#include "format.hpp"
#include "color_space.hpp"
#include "extent.hpp"
#include "image_usage.hpp"
#include "sharing_mode.hpp"
#include "swapchain.hpp" // fake

namespace vk {

enum class swapchain_create_flag {
	split_instance_bind_regions = VK_SWAPCHAIN_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT_KHR,
	рrotected = VK_SWAPCHAIN_CREATE_PROTECTED_BIT_KHR,
	mutable_format = VK_SWAPCHAIN_CREATE_MUTABLE_FORMAT_BIT_KHR
};

enum class present_mode {
	immediate = VK_PRESENT_MODE_IMMEDIATE_KHR,
	mailbox = VK_PRESENT_MODE_MAILBOX_KHR,
	fifo = VK_PRESENT_MODE_FIFO_KHR,
	fifo_relaxed = VK_PRESENT_MODE_FIFO_RELAXED_KHR,
	shared_demand_refresh_khr = VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR,
	shared_continuous_refresh_khr = VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR,
};

struct swapchain_create_info {
	u::uint_with_size_of<VkStructureType> m_type
		= VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	const void* next = nullptr;
	u::bitmask_from_enum<swapchain_create_flag> m_flags;
	vk::surface m_surface;
	uint32_t m_min_image_count;
	vk::format m_format;
	vk::color_space m_color_space;
	vk::extent<2> m_extent;
	uint32_t m_image_array_layers;
	vk::image_usage m_usage;
	vk::sharing_mode m_sharing_mode;
	uint32_t m_queue_family_index_count;
	const uint32_t* m_queue_family_indices;
	u::bitmask_from_enum<vk::surface_transform_flag> m_pre_transform;
	u::bitmask_from_enum<vk::composite_alpha_flag> m_composite_alpha;
	vk::present_mode m_present_mode;
	uint32_t m_clipped;
	vk::swapchain m_swapchain;
}; // swapchain_create_info

} // vk

static_assert(sizeof(vk::swapchain_create_info) == sizeof(VkSwapchainCreateInfoKHR));