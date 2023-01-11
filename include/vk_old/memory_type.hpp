#pragma once

#include "memory_property.hpp"

namespace vk {

	struct memory_type {
		vk::memory_properties properties;
		uint32 heap_index;
	};

} // vk