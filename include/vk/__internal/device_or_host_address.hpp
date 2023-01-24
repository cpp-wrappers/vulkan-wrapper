#pragma once

#include "./device_address.hpp"

namespace vk {

	union device_or_host_address {
		vk::device_address device_address;
		const void* host_address;
	};

} // vk
