#pragma once

#include "./handle.hpp"
#include "../__internal/device_size.hpp"
#include "../__internal/memory_offset.hpp"
#include "../__internal/memory_size.hpp"

namespace vk {

	struct mapped_memory_range {
		uint32 structure_type = 6;
		const void* next = nullptr;
		handle<vk::device_memory> memory;
		vk::memory_offset offset;
		vk::memory_size size;
	};

} // vk