#pragma once

#include <core/integer.hpp>

#include "vk/image/layout.hpp"

namespace vk {

	struct attachment_reference {
		uint32 attachment;
		vk::image_layout layout;
	};

} // vk

static_assert(sizeof(vk::attachment_reference) == sizeof(VkAttachmentReference));