#pragma once

#include <handle.hpp>
#include <integer.hpp>

namespace vk {

	struct descriptor_set;

} // vk

template<>
struct handle_underlying_t<vk::descriptor_set> {
	using type = uint64;
	static constexpr type invalid = 0;
};

template<>
struct handle_interface<vk::descriptor_set> :
	handle_interface_base<vk::descriptor_set>
{

};