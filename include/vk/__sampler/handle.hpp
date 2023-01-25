#pragma once

#include <handle.hpp>
#include <integer.hpp>

namespace vk {

	struct sampler;

} // vk

template<>
struct handle_underlying_t<vk::sampler> {
	using type = uint64;
	static constexpr type invalid = 0;
};

template<>
struct handle_interface<vk::sampler> : handle_interface_base<vk::sampler> {

};