#pragma once

#include <handle.hpp>
#include <integer.hpp>

namespace vk {

	struct acceleration_structure;

} // vk

template<>
struct handle_underlying_t<vk::acceleration_structure> {
	using type = uint64;
	static constexpr type invalid = 0;
};

template<>
struct handle_interface<vk::acceleration_structure> :
	handle_interface_base<vk::acceleration_structure>
{

};