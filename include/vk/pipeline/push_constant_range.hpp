#pragma once

#include "../shader/stage.hpp"

#include <core/integer.hpp>

namespace vk {

	struct push_constant_range {
		vk::shader_stage stage_flags;
		uint32 offset;
		uint32 size;
	};

} // vk