#pragma once

#include "../__image/layout.hpp"
#include "../__image/handle.hpp"
#include "../__image/subresource_range.hpp"
#include "../__internal/access.hpp"
#include "../__internal/queue_family_index.hpp"

#include <enum_flags.hpp>

namespace vk {

	struct old_layout : enum_flags<vk::image_layout> {};
	struct new_layout : enum_flags<vk::image_layout> {};

	struct image_memory_barrier {
		uint32 structure_type = 45;
		const void* next;
		vk::src_access src_access;
		vk::dst_access dst_access;
		vk::old_layout old_layout{ vk::image_layout::undefined };
		vk::new_layout new_layout{ vk::image_layout::undefined };
		vk::src_queue_family_index src_queue_family_index;
		vk::dst_queue_family_index dst_queue_family_index;
		handle<vk::image>::underlying_type image;
		vk::image_subresource_range subresource_range{};
	};

} // vk