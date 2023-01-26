#pragma once

#include <handle.hpp>
#include <integer.hpp>

namespace vk {

	struct device_memory;

} // vk

template<>
struct handle_underlying_t<vk::device_memory> {
	using type = uint64;
	static constexpr type invalid = 0;
};

template<>
struct handle_interface<vk::device_memory> :
	handle_interface_base<vk::device_memory>
{

};