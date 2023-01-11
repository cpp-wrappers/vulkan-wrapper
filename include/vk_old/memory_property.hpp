#pragma once

#include <core/flag_enum.hpp>

namespace vk {

	enum class memory_property {
		device_local     = 0x00000001,
		host_visible     = 0x00000002,
		host_coherent    = 0x00000004,
		host_cached      = 0x00000008,
		lazily_allocated = 0x00000010,
		_protected       = 0x00000020,
		device_coherent  = 0x00000040,
		device_uncached  = 0x00000080,
		rdma_capable     = 0x00000100,
	};
	
	using memory_properties = flag_enum<vk::memory_property>;

} // vk