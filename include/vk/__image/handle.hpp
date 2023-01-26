#pragma once

#include <handle.hpp>
#include <integer.hpp>

namespace vk {

	struct image;

} // vk

template<>
struct handle_underlying_t<vk::image> {
	using type = uint64;
	static constexpr type invalid = 0;
};

template<>
struct handle_interface<vk::image> : handle_interface_base<vk::image> {

};