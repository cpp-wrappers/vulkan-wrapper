#pragma once

#include <handle.hpp>
#include <integer.hpp>

namespace vk {

	struct swapchain;

} // vk

template<>
struct handle_underlying_t<vk::swapchain> {
	using type = uint64;
	static constexpr type invalid = 0;
};

template<>
struct handle_interface<vk::swapchain> : handle_interface_base<vk::swapchain> {

	

}; // handle<swapchain>