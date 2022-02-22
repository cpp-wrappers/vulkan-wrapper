#pragma once

#include "vk/buffer/handle.hpp"
#include "vk/format.hpp"
#include "vk/memory_offset.hpp"
#include "vk/memory_size.hpp"

namespace vk {

	struct buffer_view_create_info {
		const uint32 type = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
		const void* const next;
		const uint32 flags;
		vk::handle<vk::buffer> buffer;
		vk::format format;
		vk::memory_offset offset;
		vk::memory_size size;
	};

} // vk