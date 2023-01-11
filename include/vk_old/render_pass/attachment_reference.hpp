#pragma once

#include "../image/layout.hpp"

#include <core/integer.hpp>

namespace vk {

	struct attachment_reference {
		uint32 attachment;
		vk::image_layout layout;
	};

} // vk