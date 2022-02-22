#pragma once

#include <core/flag_enum.hpp>

#include "headers.hpp"
#include "device_size.hpp"

namespace vk {

	struct memory_heap {
		enum flag {
			device_local = VK_MEMORY_HEAP_DEVICE_LOCAL_BIT,
			multi_instance = VK_MEMORY_HEAP_MULTI_INSTANCE_BIT
		};

		vk::device_size size;
		flag_enum<flag> flags;
	};

} // vk