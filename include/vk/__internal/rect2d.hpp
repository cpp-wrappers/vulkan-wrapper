#pragma once

#include "./extent.hpp"
#include "./offset.hpp"

namespace vk {

	struct rect2d {
		vk::offset<2> offset{};
		vk::extent<2> extent{};
	};

} // vk