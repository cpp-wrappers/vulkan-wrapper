#pragma once

#include <core/array.hpp>

namespace vk {

	template<uint32 S>
	struct extent;

	template<>
	struct extent<1> : array<uint32, 1> {
		uint32& width() { return (*this)[0]; }
	};

	extent(uint32) -> extent<1>;

	template<>
	struct extent<2> : array<uint32, 2> {
		uint32& width() { return (*this)[0]; }
		uint32& height() { return (*this)[1]; }
	};

	extent(uint32, uint32) -> extent<2>;

	template<>
	struct extent<3> : array<uint32, 3> {

		extent() = default;

		extent(uint32 w, uint32 h, uint32 d) :
			array<uint32, 3>{ w, h, d }
		{}

		extent(extent<2> two_d, uint32 d) :
			array<uint32, 3>{ two_d[0], two_d[1], d }
		{}

		uint32& width() { return (*this)[0]; }
		uint32& height() { return (*this)[1]; }
		uint32& depth() { return (*this)[2]; }
	};

	extent(uint32, uint32, uint32) -> extent<3>;

} // vk