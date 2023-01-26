#pragma once

#include "../__buffer/handle.hpp"
#include "../__internal/format.hpp"
#include "../__internal/memory_offset.hpp"
#include "../__internal/memory_size.hpp"

namespace vk {

	struct buffer_view_create_info {
		uint32 structure_type = 13;
		const void* next = nullptr;
		uint32 flags = 0;
		handle<vk::buffer>::underlying_type buffer;
		vk::format format;
		vk::memory_offset offset;
		vk::memory_size size;
	};

} // vk