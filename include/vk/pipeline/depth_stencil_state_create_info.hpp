#pragma once

#include <core/integer.hpp>

#include "../compare_op.hpp"
#include "../stencil_op_state.hpp"

namespace vk {

	struct pipeline_depth_stencil_state_create_info {
		uint32 structure_type = 25;
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

} // vk