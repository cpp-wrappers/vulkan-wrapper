#pragma once

#include <core/integer.hpp>
#include <core/flag_enum.hpp>
#include <core/wrapper/of_integer.hpp>
#include <core/wrapper/of_pointer_to.hpp>

#include "../shared/headers.hpp"
//#include "../surface/surface.hpp"
#include "../image/format.hpp"
#include "../image/color_space.hpp"
#include "../shared/extent.hpp"
#include "../image/usage.hpp"
#include "../shared/sharing_mode.hpp"
#include "../shared/queue_family_index.hpp"
#include "../surface/transform.hpp"
#include "../surface/composite_alpha.hpp"

namespace vk {

	class swapchain;
	class surface;

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

	struct min_image_count : wrapper::of_integer<uint32> {};
	struct image_array_layers : wrapper::of_integer<uint32> {};
	struct queue_family_index_count : wrapper::of_integer<uint32> {};
	struct queue_family_indices : wrapper::of_pointer_to<const vk::queue_family_index> {};
	struct clipped : wrapper::of_integer<uint32> {};

	struct swapchain_create_info {
		uint32 type = (uint32) VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		const void* next{};
		flag_enum<swapchain_create_flag> flags{};
		void* surface;
		vk::min_image_count min_image_count{};
		vk::format format{};
		vk::color_space color_space{};
		vk::extent<2u> extent{};
		vk::image_array_layers image_array_layers{ 1u };
		vk::image_usage usage{};
		vk::sharing_mode sharing_mode{};
		vk::queue_family_index_count queue_family_index_count{};
		vk::queue_family_indices queue_family_indices{};
		flag_enum<vk::surface_transform> pre_transform{};
		flag_enum<vk::composite_alpha> composite_alpha{};
		vk::present_mode present_mode{};
		vk::clipped clipped{};
		void* swapchain;
	}; // swapchain_create_info

} // vk

static_assert(sizeof(vk::swapchain_create_info) == sizeof(VkSwapchainCreateInfoKHR));