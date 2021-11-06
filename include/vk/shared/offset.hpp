#pragma once

#include <core/wrapper/of_integer.hpp>

#include "headers.hpp"

namespace vk {

	template<uint Dim = 1>
	struct offset;

	template<>
	struct offset<1u> : wrapper::of_integer<uint32> {};

	offset(uint32) -> offset<1u>;

	template<>
	struct offset<2u> {
		uint32 x, y;
	};

}

static_assert(sizeof(vk::offset<2u>) == sizeof(VkOffset2D));