#pragma once

#include <core/integer.hpp>

#include "../../shared/headers.hpp"
#include "../../shared/polygon_mode.hpp"
#include "../../shared/cull_mode.hpp"
#include "../../shared/front_face.hpp"

namespace vk {

	struct pipeline_rasterization_state_create_info {
		const uint32 type = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		const void* const next;
		uint32 flags;
		uint32 enable_depth_clamp;
		uint32 enable_rasterizer_discard;
		vk::polygon_mode polygon_mode;
		vk::cull_mode cull_mode;
		vk::front_face front_face;
		uint32 enable_depth_bias;
		float depth_bias_constant_factor;
		float depth_bias_clamp;
		float depth_bias_slope_factor;
		float line_width{ 1.0 };
	};

} // vk

static_assert(sizeof(vk::pipeline_rasterization_state_create_info) == sizeof(VkPipelineRasterizationStateCreateInfo));