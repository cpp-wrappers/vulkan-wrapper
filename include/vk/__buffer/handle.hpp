#pragma once

#include <handle.hpp>
#include <integer.hpp>

namespace vk {

	struct buffer;

} // vk

template<>
struct handle_underlying_t<vk::buffer> {
	using type = uint64;
	static constexpr type invalid = 0;
};

template<>
struct handle_interface<vk::buffer> : handle_interface_base<vk::buffer> {

};