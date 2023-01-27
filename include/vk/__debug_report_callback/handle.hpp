#pragma once

#include <handle.hpp>
#include <integer.hpp>

namespace vk {

	struct debug_report_callback;

} // vk

template<>
struct handle_underlying_t<vk::debug_report_callback> {
	using type = uint64;
	static constexpr type invalid = 0;
};

template<>
struct handle_interface<vk::debug_report_callback> :
	handle_interface_base<vk::debug_report_callback>
{

};