#pragma once

#include <handle.hpp>
#include <integer.hpp>

namespace vk {

	struct buffer_view;

} // vk

template<>
struct handle_underlying_t<vk::buffer_view> {
	using type = uint64;
	static constexpr type invalid = 0;
};

template<>
struct handle_interface<vk::buffer_view> :
	handle_interface_base<vk::buffer_view>
{

};