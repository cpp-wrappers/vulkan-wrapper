#pragma once

#include <core/integer.hpp>

#include "../headers.hpp"

namespace vk {

	struct pipeline_tesselation_state_create_info {
		const uint32 type = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
		const void* const next;
		uint32 patch_control_points;
	};

} // vk

static_assert(sizeof(vk::pipeline_tesselation_state_create_info) == sizeof(VkPipelineTessellationStateCreateInfo));