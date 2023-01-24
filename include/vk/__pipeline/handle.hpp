#pragma once

#include <handle.hpp>
#include <integer.hpp>

namespace vk {

	struct pipeline;

} // vk

template<>
struct handle_underlying_t<vk::pipeline> {
	using type = uint64;
	static constexpr type invalid = 0;
};

template<>
struct handle_interface<vk::pipeline> :
	handle_interface_base<vk::pipeline>
{

};