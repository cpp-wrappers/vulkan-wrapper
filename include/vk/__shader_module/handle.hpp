#pragma once

#include <handle.hpp>
#include <integer.hpp>

namespace vk {

	struct shader_module;

} // vk

template<>
struct handle_underlying_t<vk::shader_module> {
	using type = uint64;
	static constexpr type invalid = 0;
};

template<>
struct handle_interface<vk::shader_module> :
	handle_interface_base<vk::shader_module>
{
	
};