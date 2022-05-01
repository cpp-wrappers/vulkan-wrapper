#pragma once

#include "../../buffer/handle.hpp"
#include "../../format.hpp"
#include "../../memory_offset.hpp"
#include "../../memory_size.hpp"

namespace vk {

	struct buffer_view_create_info {
		uint32             structure_type = 13;
		const void*        next = nullptr;
		uint32             flags = 0;
		handle<vk::buffer> buffer;
		vk::format         format;
		vk::memory_offset  offset;
		vk::memory_size    size;
	};

} // vk