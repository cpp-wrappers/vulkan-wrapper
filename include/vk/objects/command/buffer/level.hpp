#pragma once

#include "../../../shared/headers.hpp"

namespace vk {

	enum class command_buffer_level {
		primary = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		secondary = VK_COMMAND_BUFFER_LEVEL_SECONDARY
	};

}