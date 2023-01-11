#pragma once

#include "handle.hpp"
#include "../../device_size.hpp"
#include "../../memory_offset.hpp"
#include "../../memory_size.hpp"

#include <core/integer.hpp>

namespace vk {

	struct mapped_memory_range {
		uint32 structure_type = 6;
		const void* next = nullptr;
		handle<vk::device_memory> memory;
		vk::memory_offset offset;
		vk::memory_size size;
	};

} // vk