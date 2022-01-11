#pragma once

#include "../../../shared/headers.hpp"
#include "../../buffer/view/handle.hpp"
#include "../binding.hpp"
#include "../type.hpp"
#include "../image_info.hpp"
#include "../buffer_info.hpp"
#include "../array_element.hpp"
#include "handle.hpp"

namespace vk {

	struct write_descriptor_set {
		const uint32 type = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		const void* const next;
		vk::handle<vk::descriptor_set> dst_set;
		vk::dst_binding dst_binding;
		vk::dst_array_element dst_array_element;
		vk::descriptor_type descriptor_type;
		const vk::descriptor_image_info* image_info;
		const vk::descriptor_buffer_info* buffer_info;
		const vk::handle<vk::buffer_view>* texel_buffer_view;
	};

} // vk

static_assert(sizeof(vk::write_descriptor_set) == sizeof(VkWriteDescriptorSet));