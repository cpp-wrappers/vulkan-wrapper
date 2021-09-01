#pragma once

#include "headers.hpp"
#include <core/integer.hpp>
#include "attachment_description.hpp"

namespace vk {

struct render_pass_create_info {
	uint_with_size_of<VkStructureType> m_type = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	const void* m_next = nullptr;
	uint_with_size_of<VkRenderPassCreateFlags> m_glags = 0;
	uint32_t m_attachment_count = 0;
	vk::attachment_description* m_attachments = 0;
};

}