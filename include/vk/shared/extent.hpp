#pragma once

#include <core/array.hpp>

namespace vk {

template<uint32 S>
struct extent;

template<>
struct extent<1u> : array<uint32, 1u> {
	uint32& width() { return (*this)[0u]; }
};

template<>
struct extent<2u> : array<uint32, 2u> {
	uint32& width() { return (*this)[0u]; }
	uint32& height() { return (*this)[1u]; }
};

template<>
struct extent<3u> : array<uint32, 3u> {
	uint32& width() { return (*this)[0u]; }
	uint32& height() { return (*this)[1u]; }
	uint32& depth() { return (*this)[2u]; }
};

}