#pragma once

#include <handle.hpp>
#include <integer.hpp>

namespace vk {

	struct image_view;

} // vk

template<>
struct handle_underlying_t<vk::image_view> {
	using type = uint64;
	static constexpr type invalid = 0;
};

template<>
struct handle_interface<vk::image_view> :
	handle_interface_base<vk::image_view>
{

};