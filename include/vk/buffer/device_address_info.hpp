#pragma once

#include "handle.hpp"

namespace vk {

	struct buffer_device_address_info {
		uint32 structure_type = 1000244001;
		const void* next = nullptr;
		handle<vk::buffer> buffer;
	};

} // vk