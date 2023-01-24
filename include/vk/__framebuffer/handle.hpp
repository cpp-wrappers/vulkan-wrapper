#pragma once

#include <handle.hpp>
#include <integer.hpp>

namespace vk {

	struct framebuffer;

} // vk

template<>
struct handle_underlying_t<vk::framebuffer> {
	using type = uint64;
	static constexpr type invalid = 0;
};

template<>
struct handle_interface<vk::framebuffer> :
	handle_interface_base<vk::framebuffer>
{
	
};