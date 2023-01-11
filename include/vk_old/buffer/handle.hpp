#pragma once

#include "../handle/base.hpp"
#include "../create_or_allocate.hpp"

#include <core/handle.hpp>

namespace vk {

	struct buffer;

	template<>
	inline constexpr bool is_creatable<vk::buffer> = true;

} // vk

template<>
struct handle<vk::buffer> : vk::handle_base<vk::non_dispatchable> {};