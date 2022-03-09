#pragma once

#include "vk/headers.hpp"

namespace vk {

	struct transform_matrix {
		float data[3][4];
	};

} // vk

static_assert(sizeof(vk::transform_matrix) == sizeof(VkTransformMatrixKHR));