#pragma once

#include <handle.hpp>
#include <integer.hpp>

namespace vk {

	struct render_pass;

} // vk

template<>
struct handle_underlying_t<vk::render_pass> {
	using type = uint64;
	static constexpr type invalid = 0;
};

template<>
struct handle_interface<vk::render_pass> :
	handle_interface_base<vk::render_pass>
{
	
};