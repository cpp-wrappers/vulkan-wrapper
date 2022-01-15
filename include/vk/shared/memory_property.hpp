#pragma once

#include <core/flag_enum.hpp>

#include "headers.hpp"

namespace vk {

	enum class memory_property {
		device_local = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		host_visible = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
		host_coherent = VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		host_cached = VK_MEMORY_PROPERTY_HOST_CACHED_BIT,
		lazily_allocated = VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT,
		__protected = VK_MEMORY_PROPERTY_PROTECTED_BIT,
		device_coherent = VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD,
		device_uncached = VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD,
		//rdma_capable = VK_MEMORY_PROPERTY_RDMA_CAPABLE_BIT_NV,
	};
	
	using memory_properties = flag_enum<vk::memory_property>;

}