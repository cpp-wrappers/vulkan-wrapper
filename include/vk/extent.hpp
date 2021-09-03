#pragma once

#include <array>

namespace vk {

template<uint32_t S>
struct extent;

template<>
struct extent<1> : std::array<uint32_t, 1> {
	uint32_t& width() { return (*this)[0]; }
};

template<>
struct extent<2> : std::array<uint32_t, 2> {
	uint32_t& width() { return (*this)[0]; }
	uint32_t& height() { return (*this)[1]; }
};

template<>
struct extent<3> : std::array<uint32_t, 3> {
	uint32_t& width() { return (*this)[0]; }
	uint32_t& height() { return (*this)[1]; }
	uint32_t& depth() { return (*this)[3]; }
};

}