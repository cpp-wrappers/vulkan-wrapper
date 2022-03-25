#pragma once

#include "handle.hpp"

namespace vk {

	struct buffer_memory_requirements_info_2 {
		uint32 structure_type = 1000146000;
		const void* next = nullptr;
		handle<vk::buffer> buffer;
	};

} // vk