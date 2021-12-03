#pragma once

#include <core/integer.hpp>

#include "../shared/headers.hpp"
#include "../shared/logic_op.hpp"
#include "color_blend_attachment_state.hpp"

namespace vk {

	struct pipeline_color_blend_state_create_info {
		const uint32 type = (uint32) VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		const void* next{};
		const uint32 flags{};
		uint32 enable_logic_op{ VK_FALSE };
		vk::logic_op logic_op;
		uint32 attachment_count{};
		const pipeline_color_blend_attachment_state* attachments{};
		float blend_constants[4]{};
	};

}

static_assert(sizeof(vk::pipeline_color_blend_state_create_info) == sizeof(VkPipelineColorBlendStateCreateInfo));