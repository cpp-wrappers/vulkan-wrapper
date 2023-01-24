#pragma once

#include <handle.hpp>
#include <integer.hpp>

namespace vk {

	struct semaphore;

} // vk

template<>
struct handle_underlying_t<vk::semaphore> {
	using type = uint64;
	static constexpr type invalid = 0;
};

template<>
struct handle_interface<vk::semaphore> : handle_interface_base<vk::semaphore> {
	
};