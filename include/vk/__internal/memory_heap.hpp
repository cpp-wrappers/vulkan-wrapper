#pragma once

#include "./device_size.hpp"

#include <enum_flags.hpp>

namespace vk {

	struct memory_heap {

		enum flag {
			device_local   = 0x00000001,
			multi_instance = 0x00000002
		};

		vk::device_size size;
		enum_flags<flag> flags;
	};

} // vk