#pragma once

#include "headers.hpp"
#include <cstdint>
#include <core/integer.hpp>
#include <core/flag_enum.hpp>
#include "surface.hpp"
#include "format.hpp"
#include "color_space.hpp"
#include "extent.hpp"
#include "image_usage.hpp"
#include "sharing_mode.hpp"
#include "queue_family_index.hpp"

namespace vk {

class swapchain;

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

struct min_image_count : named<uint32_t> {};
struct image_array_layers : named<uint32_t> {};
struct queue_family_index_count : named<uint32_t> {};
struct queue_family_indices : named<const vk::queue_family_index*> {};
struct clipped : named<uint32_t> {};

struct swapchain_create_info {
	uint_with_size_of<VkStructureType> type = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	const void* next{};
	flag_enum<swapchain_create_flag> flags{};
	vk::surface* surface{};
	vk::min_image_count min_image_count{};
	vk::format format{};
	vk::color_space color_space{};
	vk::extent<2> extent{};
	vk::image_array_layers image_array_layers{ 1 };
	vk::image_usage usage{};
	vk::sharing_mode sharing_mode{};
	vk::queue_family_index_count queue_family_index_count{};
	vk::queue_family_indices queue_family_indices{};
	flag_enum<vk::surface_transform_flag> pre_transform{};
	flag_enum<vk::composite_alpha_flag> composite_alpha{};
	vk::present_mode present_mode{};
	vk::clipped clipped{};
	vk::swapchain* swapchain{};
}; // swapchain_create_info

} // vk

static_assert(sizeof(vk::swapchain_create_info) == sizeof(VkSwapchainCreateInfoKHR));