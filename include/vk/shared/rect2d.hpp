#pragma once

#include "extent.hpp"
#include "offset.hpp"

namespace vk {

	struct rect2d {
		vk::offset<2u> offset;
		vk::extent<2u> extent;
	};

}