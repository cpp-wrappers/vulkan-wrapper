#pragma once

#include <core/integer.hpp>

#include "../headers.hpp"
#include "../polygon_mode.hpp"
#include "../cull_mode.hpp"
#include "../front_face.hpp"

namespace vk {

	struct pipeline_rasterization_state_create_info {
		uint32 type = (primitive::uint32) VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		const void* next{};
		uint32 flags;
		uint32 enable_depth_clamp;
		uint32 enable_rasterizer_discard;
		vk::polygon_mode polygon_mode;
		vk::cull_mode cull_mode;
		vk::front_face front_face;
		uint32 enable_depth_bias;
		float depth_bias_constant_factor{};
		float depth_bias_clamp{};
		float depth_bias_slope_factor{};
		float line_width{};
	};

}

static_assert(sizeof(vk::pipeline_rasterization_state_create_info) == sizeof(VkPipelineRasterizationStateCreateInfo));