#pragma once

#include <handle.hpp>

namespace vk {

	struct command_buffer;

} // vk

template<>
struct handle_underlying_t<vk::command_buffer> {
	using type = vk::command_buffer*;
	static constexpr type invalid = nullptr;
};

template<>
struct handle_interface<vk::command_buffer> :
	handle_interface_base<vk::command_buffer>
{

};