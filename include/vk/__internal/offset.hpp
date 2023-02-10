#pragma once

#include <integer.hpp>

namespace vk {

	template<nuint Dim = 1>
	struct offset;

	template<>
	struct offset<1> {
		int32 value_ = 0;

		offset() = default;
		offset(int32 value) : value_{ value } {}
		operator int32() const { return value_; }
		operator uint32() const { return value_; }
	};

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

} // vk