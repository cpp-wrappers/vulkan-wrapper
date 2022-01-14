#pragma once

#include <core/integer.hpp>

#include "../../../shared/headers.hpp"
#include "../../../shared/access.hpp"
#include "../../../shared/queue_family_index.hpp"
#include "../../image/layout.hpp"
#include "../../image/handle.hpp"
#include "../../image/subresource_range.hpp"

namespace vk {

	struct old_layout : flag_enum<vk::image_layout> {};
	struct new_layout : flag_enum<vk::image_layout> {};
	struct src_queue_family_index : queue_family_index {};
	struct dst_queue_family_index : queue_family_index {};

	struct image_memory_barrier {
		uint32 type = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		const void* const next = nullptr;
		vk::src_access src_access;
		vk::dst_access dst_access;
		vk::old_layout old_layout;
		vk::new_layout new_layout;
		vk::src_queue_family_index src_queue_family_index;
		vk::dst_queue_family_index dst_queue_family_index;
		vk::handle<vk::image> image;
		vk::image_subresource_range subresource_range;
	};

} // vk

static_assert(sizeof(vk::image_memory_barrier) == sizeof(VkImageMemoryBarrier));