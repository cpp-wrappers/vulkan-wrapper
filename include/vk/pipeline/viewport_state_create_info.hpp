#pragma once

#include <core/integer.hpp>

#include "../shared/headers.hpp"
#include "../shared/viewport.hpp"
#include "../shared/rect2d.hpp"

namespace vk {

	struct pipeline_viewport_state_create_info {
		const uint32 type = (uint32) VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		const void* next{};
		uint32 flags{};
		uint32 viewport_count{};
		const vk::viewport* viewports{};
		uint32 scissor_count{};
		const vk::rect2d* scissors{};
	};
}

static_assert(sizeof(vk::pipeline_viewport_state_create_info) == sizeof(VkPipelineViewportStateCreateInfo));