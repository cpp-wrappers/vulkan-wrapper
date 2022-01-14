#pragma once

#include "../image/layout.hpp"
#include <core/integer.hpp>

namespace vk {

	struct attachment_reference {
		uint32 attachment;
		vk::image_layout layout;
	};

} // vk

static_assert(sizeof(vk::attachment_reference) == sizeof(VkAttachmentReference));