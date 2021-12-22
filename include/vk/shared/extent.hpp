#pragma once

#include <core/array.hpp>

namespace vk {

	template<uint32 S>
	struct extent;

	template<>
	struct extent<1> : array<uint32, 1> {
		uint32& width() { return (*this)[0u]; }
	};

	extent(uint32) -> extent<1>;

	template<>
	struct extent<2> : array<uint32, 2> {
		uint32& width() { return (*this)[0u]; }
		uint32& height() { return (*this)[1u]; }
	};

	extent(uint32, uint32) -> extent<2>;

	template<>
	struct extent<3> : array<uint32, 3> {
		uint32& width() { return (*this)[0u]; }
		uint32& height() { return (*this)[1u]; }
		uint32& depth() { return (*this)[2u]; }
	};

	extent(uint32, uint32, uint32) -> extent<3>;
}