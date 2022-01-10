#pragma once

#include <core/integer.hpp>

#include "../../shared/headers.hpp"
#include "../../shared/compare_op.hpp"
#include "../../shared/stencil_op_state.hpp"

namespace vk {

	struct pipeline_depth_stencil_state_create_info {
		const uint32 type = (uint32) VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		const void* next;
		uint32 flags;
		uint32 enable_depth_test;
		uint32 enable_depth_write;
		vk::compare_op depth_compare_op;
		uint32 enable_depth_bounds_test;
		uint32 enable_stencil_test;
		vk::stencil_op_state front;
		vk::stencil_op_state back;
		float min_depth_bounds;
		float max_depth_bounds;
	};
}

static_assert(sizeof(vk::pipeline_depth_stencil_state_create_info) == sizeof(VkPipelineDepthStencilStateCreateInfo));