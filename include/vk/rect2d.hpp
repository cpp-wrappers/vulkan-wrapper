#pragma once

#include "headers.hpp"
#include "extent.hpp"
#include "offset.hpp"

namespace vk {
	struct rect2d {
		vk::offset<2> offset{};
		vk::extent<2> extent{};
	};
}

static_assert(sizeof(vk::rect2d) == sizeof(VkRect2D));