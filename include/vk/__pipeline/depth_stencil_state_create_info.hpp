#pragma once

#include <integer.hpp>

#include "../__internal/compare_op.hpp"
#include "../__internal/stencil_op_state.hpp"

namespace vk {

	struct pipeline_depth_stencil_state_create_info {
		uint32               structure_type = 25;
		const void*          next = nullptr;
		uint32               flags = 0;
		uint32               enable_depth_test { false };
		uint32               enable_depth_write { false };
		vk::compare_op       depth_compare_op;
		uint32               enable_depth_bounds_test { false };
		uint32               enable_stencil_test { false };
		vk::stencil_op_state front{};
		vk::stencil_op_state back{};
		float                min_depth_bounds = 0.0F;
		float                max_depth_bounds = 0.0F;
	};

} // vk