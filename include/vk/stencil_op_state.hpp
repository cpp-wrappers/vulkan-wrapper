#pragma once

#include "stencil_op.hpp"
#include "compare_op.hpp"

namespace vk {

	struct stencil_op_state {
		vk::stencil_op fail_op{};
		vk::stencil_op pass_op{};
		vk::stencil_op depth_fail_op{};
		vk::compare_op compare_op{};
		uint32 compare_mask;
		uint32 write_mask;
		uint32 reference;
	};
}

static_assert(sizeof(vk::stencil_op_state) == sizeof(VkStencilOpState));