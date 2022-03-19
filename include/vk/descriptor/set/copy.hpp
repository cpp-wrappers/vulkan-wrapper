#pragma once

#include "handle.hpp"

#include "vk/headers.hpp"
#include "vk/descriptor/binding.hpp"
#include "vk/descriptor/array_element.hpp"
#include "vk/descriptor/count.hpp"

namespace vk {

	struct copy_descriptor_set {
		const uint32 type = VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET;
		const void* const next;
		handle<vk::descriptor_set> src_set;
		vk::src_binding src_binding;
		vk::src_array_element src_array_element;
		handle<vk::descriptor_set> dst_set;
		vk::dst_binding dst_binding;
		vk::dst_array_element dst_array_element;
		vk::descriptor_count descriptor_count;
	};

} // vk

static_assert(sizeof(vk::copy_descriptor_set) == sizeof(VkCopyDescriptorSet));