#pragma once

#include <handle.hpp>
#include <integer.hpp>

namespace vk {

	struct fence;

} // vk

template<>
struct handle_underlying_t<vk::fence> {
	using type = uint64;
	static constexpr type invalid = 0;
};

template<>
struct handle_interface<vk::fence> : handle_interface_base<vk::fence> {
	
};