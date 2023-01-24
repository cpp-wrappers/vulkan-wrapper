#pragma once

#include "../__instance/handle.hpp"

#include <handle.hpp>
#include <integer.hpp>
#include <body.hpp>

namespace vk {

	struct surface;

} // vk

template<>
struct handle_underlying_t<vk::surface> {
	using type = uint64;
	static constexpr type invalid = 0;
};

template<>
struct handle_interface<vk::surface> : handle_interface_base<vk::surface> {

};