#pragma once

#include "./handle.hpp"

#include "../__internal/sharing_mode.hpp"
#include "../__internal/queue_family_index.hpp"
#include "../__internal/extent.hpp"
#include "../__internal/format.hpp"
#include "../__surface/present_mode.hpp"
#include "../__image/color_space.hpp"
#include "../__image/usage.hpp"
#include "../__surface/transform.hpp"
#include "../__surface/composite_alpha.hpp"
#include "../__surface/min_image_count.hpp"
#include "../__surface/handle.hpp"

#include <enum_flags.hpp>

namespace vk {

	enum class swapchain_create_flag {
		split_instance_bind_regions = 0x00000001,
		_protected                  = 0x00000002,
		mutable_format              = 0x00000004
	};

	struct image_array_layers       { uint32 _; };
	struct queue_family_index_count { uint32 _; };
	struct queue_family_indices { const vk::queue_family_index* _; };

	struct clipped { uint32 _; };

	struct swapchain_create_info {
		uint32                                 structure_type = 1000001000;
		const void*                            next = nullptr;
		enum_flags<swapchain_create_flag>      flags;
		handle<vk::surface>::underlying_type   surface;
		vk::min_image_count                    min_image_count;
		vk::format                             format;
		vk::color_space                        color_space;
		vk::extent<2>                          extent;
		vk::image_array_layers                 image_array_layers{ 1 };
		vk::image_usages                       usage;
		vk::sharing_mode                       sharing_mode;
		vk::queue_family_index_count           queue_family_index_count;
		vk::queue_family_indices               queue_family_indices;
		enum_flags<vk::surface_transform>      pre_transform;
		enum_flags<vk::composite_alpha>        composite_alpha;
		vk::present_mode                       present_mode;
		vk::clipped                            clipped;
		handle<vk::swapchain>::underlying_type old_swapchain{};
	};

} // vk