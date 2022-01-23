#pragma once

#include <core/wrapper/of_integer.hpp>

#include "headers.hpp"

namespace vk {

	template<nuint Dim>
	struct offset;

	template<>
	struct offset<1> : wrapper::of_integer<int32> {};

	offset(int32) -> offset<1>;

	template<>
	struct offset<2> {
		int32 x, y;
	};

	offset(int32, int32) -> offset<2>;

	template<>
	struct offset<3> {
		int32 x, y, z;
	};

	offset(int32, int32, int32) -> offset<3>;

}

static_assert(sizeof(vk::offset<2>) == sizeof(VkOffset2D));
static_assert(sizeof(vk::offset<3>) == sizeof(VkOffset3D));