#pragma once

#include "device_size.hpp"

#include <core/flag_enum.hpp>

namespace vk {

	struct memory_heap {

		enum flag {
			device_local   = 0x00000001,
			multi_instance = 0x00000002
		};

		vk::device_size size;
		flag_enum<flag> flags;
	};

} // vk