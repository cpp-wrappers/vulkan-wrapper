#pragma once

#include <handle.hpp>
#include <integer.hpp>

namespace vk {

	struct descriptor_pool;

} // vk

template<>
struct handle_underlying_t<vk::descriptor_pool> {
	using type = uint64;
	static constexpr type invalid = 0;
};

template<>
struct handle_interface<vk::descriptor_pool> :
	handle_interface_base<vk::descriptor_pool>
{

};