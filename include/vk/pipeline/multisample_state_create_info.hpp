#pragma once

#include <core/integer.hpp>

#include "../headers.hpp"
#include "../sample_count.hpp"

namespace vk {

	struct pipeline_multisample_state_create_info {
		uint32 type = (primitive::uint32) VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		const void* next{};
		uint32 flags;
		vk::sample_count rasterization_samples{0};
		uint32 enable_sample_shading;
		float min_sample_shading{};
		const uint32* sample_mask{};
		uint32 enable_alpha_to_coverage;
		uint32 enable_alpha_to_one;
	};

}

static_assert(sizeof(vk::pipeline_multisample_state_create_info) == sizeof(VkPipelineMultisampleStateCreateInfo));