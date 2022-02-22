#pragma once

#include <core/integer.hpp>

#include "vk/headers.hpp"
#include "vk/shader/stage.hpp"

namespace vk {

	struct push_constant_range {
		vk::shader_stage stage_flags;
		uint32 offset;
		uint32 size;
	};

} // vk

static_assert(sizeof(vk::push_constant_range) == sizeof(VkPushConstantRange));