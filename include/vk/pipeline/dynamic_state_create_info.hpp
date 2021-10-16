#pragma once

#include <core/integer.hpp>

#include "../headers.hpp"
#include "../dynamic_state.hpp"

namespace vk {
	struct pipeline_dynamic_state_create_info {
		const uint32 type = (primitive::uint32) VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		const void* next{};
		const uint32 flags;
		uint32 dynamic_state_count;
		const dynamic_state* dynamic_states;
	};
}

static_assert(sizeof(vk::pipeline_dynamic_state_create_info) == sizeof(VkPipelineDynamicStateCreateInfo));