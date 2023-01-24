#pragma once

#include "../__shader_module/stage.hpp"

#include <integer.hpp>

namespace vk {

	struct push_constant_range {
		vk::shader_stages stages;
		uint32            offset;
		uint32            size;
	};

} // vk