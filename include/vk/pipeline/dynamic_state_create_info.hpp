#pragma once

#include <core/integer.hpp>
#include <core/range/of_value_type.hpp>

#include "vk/headers.hpp"
#include "vk/dynamic_state.hpp"

namespace vk {
	struct pipeline_dynamic_state_create_info {
		const uint32 type = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		const void* const next{};
		uint32 flags{};
		uint32 dynamic_state_count;
		const dynamic_state* dynamic_states;

		pipeline_dynamic_state_create_info(const range::of_value_type<vk::dynamic_state> auto& dynamic_states)
		:
			dynamic_state_count { (uint32) dynamic_states.size() },
			dynamic_states { dynamic_states.data() }
		{}
	};
}

static_assert(sizeof(vk::pipeline_dynamic_state_create_info) == sizeof(VkPipelineDynamicStateCreateInfo));