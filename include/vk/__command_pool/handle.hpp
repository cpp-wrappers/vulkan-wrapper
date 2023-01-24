#pragma once

#include <handle.hpp>
#include <integer.hpp>

namespace vk {

	struct command_pool;

} // vk

template<>
struct handle_underlying_t<vk::command_pool> {
	using type = uint64;
	static constexpr type invalid = 0;
};

template<>
struct handle_interface<vk::command_pool> :
	handle_interface_base<vk::command_pool>
{

};
