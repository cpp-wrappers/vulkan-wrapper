#pragma once

#include <handle.hpp>

namespace vk {

	struct queue;

} // vk

template<>
struct handle_underlying_t<vk::queue> {
	using type = vk::queue*;
	static constexpr type invalid = nullptr;
};

template<>
struct handle_interface<vk::queue> : handle_interface_base<vk::queue> {
};