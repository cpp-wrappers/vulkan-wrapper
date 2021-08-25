#pragma once

#include "shader_stage.hpp"

namespace vk {

struct push_constant_range {
	vk::shader_stage stage_flags;
	uint32_t offset;
	uint32_t size;
};

} // vk

static_assert(sizeof(vk::push_constant_range) == sizeof(VkPushConstantRange));