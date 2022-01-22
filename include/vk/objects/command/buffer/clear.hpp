#pragma once

#include "../../../shared/headers.hpp"

#include <core/integer.hpp>

namespace vk {

	struct clear_color_value {
		float r, g, b, a;
	};

	struct clear_depth_stencil_value {
		float depth;
		uint32 stencil;
	};

	union clear_value {
		clear_color_value color;
		clear_depth_stencil_value depth_stencil;
	};

} // vk

static_assert(sizeof(vk::clear_color_value) == sizeof(VkClearColorValue));
static_assert(sizeof(vk::clear_depth_stencil_value) == sizeof(VkClearDepthStencilValue));
static_assert(sizeof(vk::clear_value) == sizeof(VkClearValue));