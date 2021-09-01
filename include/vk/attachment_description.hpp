#pragma once 

#include "headers.hpp"
#include <core/flag_enum.hpp>
#include <vulkan/vulkan_core.h>
#include "format.hpp"
#include "sample_count.hpp"
#include "attachment_load_op.hpp"
#include "attachment_store_op.hpp"
#include "image_layout.hpp"

namespace vk {

enum class attachment_description_flag {
	may_alias = VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT
};

struct attachment_description {
	flag_enum<attachment_description_flag> m_flags;
	vk::format m_format;
	vk::sample_count m_samples;
	vk::attachment_load_op m_load_op;
	vk::attachment_store_op m_store_op;
	vk::attachment_load_op m_stencil_load_op;
	vk::attachment_store_op m_stencil_store_op;
	vk::image_layout m_initial_layout;
	vk::image_layout m_final_layout;
};

}

static_assert(sizeof(vk::attachment_description) == sizeof(VkAttachmentDescription));