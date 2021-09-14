#pragma once

#include <cstdint>
#include <vulkan/vulkan_core.h>
#include "image/layout.hpp"

namespace vk {

struct attachment_reference {
	uint32_t attachment;
	vk::image_layout layout;
};

}

static_assert(sizeof(vk::attachment_reference) == sizeof(VkAttachmentReference));