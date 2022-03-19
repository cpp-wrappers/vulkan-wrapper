#pragma once

#include "vk/headers.hpp"
#include "vk/memory_offset.hpp"
#include "vk/memory_size.hpp"
#include "vk/buffer/handle.hpp"

namespace vk {

	struct descriptor_buffer_info {
		handle<vk::buffer> buffer;
		vk::memory_offset offset;
		vk::memory_size size;
	};

} // vk

static_assert(sizeof(vk::descriptor_buffer_info) == sizeof(VkDescriptorBufferInfo));