#pragma once

#include "../__image/layout.hpp"

#include <integer.hpp>

namespace vk {

	struct attachment_reference {
		uint32 attachment;
		vk::image_layout layout;
	};

} // vk