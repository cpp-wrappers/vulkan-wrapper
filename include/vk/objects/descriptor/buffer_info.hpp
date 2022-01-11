#pragma once

#include "../../shared/headers.hpp"
#include "../../shared/memory_offset.hpp"
#include "../../shared/memory_size.hpp"
#include "../buffer/handle.hpp"

namespace vk {

	struct descriptor_buffer_info {
		vk::handle<vk::buffer> buffer;
		vk::memory_offset offset;
		vk::memory_size size;
	};

} // vk

static_assert(sizeof(vk::descriptor_buffer_info) == sizeof(VkDescriptorBufferInfo));