#pragma once

#include "../__internal/object_type.hpp"

#include <handle.hpp>
#include <integer.hpp>

namespace vk {

	struct buffer;

	template<>
	struct object_type_t<vk::buffer> {
		static constexpr auto value = vk::object_type::buffer;
	};

} // vk

template<>
struct handle_underlying_t<vk::buffer> {
	using type = uint64;
	static constexpr type invalid = 0;
};

template<>
struct handle_interface<vk::buffer> : handle_interface_base<vk::buffer> {

};