#pragma once

#include <core/integer.hpp>

#include "../shared/headers.hpp"

namespace vk {

	struct pipeline_tesselation_state_create_info {
		uint32 type = (uint32) VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
		const void* next{};
		uint32 patch_control_points;
	};
}

static_assert(sizeof(vk::pipeline_tesselation_state_create_info) == sizeof(VkPipelineTessellationStateCreateInfo));