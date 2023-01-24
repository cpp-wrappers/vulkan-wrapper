#pragma once

#include <handle.hpp>
#include <integer.hpp>

namespace vk {

	struct pipeline_layout;

} // vk

template<>
struct handle_underlying_t<vk::pipeline_layout> {
	using type = uint64;
	static constexpr type invalid = 0;
};

template<>
struct handle_interface<vk::pipeline_layout> :
	handle_interface_base<vk::pipeline_layout>
{

};