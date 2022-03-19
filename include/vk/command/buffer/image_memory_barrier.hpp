#pragma once

#include "vk/headers.hpp"
#include "vk/access.hpp"
#include "vk/queue_family_index.hpp"
#include "vk/image/layout.hpp"
#include "vk/image/handle.hpp"
#include "vk/image/subresource_range.hpp"

namespace vk {

	struct old_layout : flag_enum<vk::image_layout> {};
	struct new_layout : flag_enum<vk::image_layout> {};

	struct image_memory_barrier {
		uint32 structure_type = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		const void* next;
		vk::src_access src_access;
		vk::dst_access dst_access;
		vk::old_layout old_layout{ vk::image_layout::undefined };
		vk::new_layout new_layout{ vk::image_layout::undefined };
		vk::src_queue_family_index src_queue_family_index;
		vk::dst_queue_family_index dst_queue_family_index;
		handle<vk::image> image;
		vk::image_subresource_range subresource_range;
	};

} // vk

static_assert(sizeof(vk::image_memory_barrier) == sizeof(VkImageMemoryBarrier));