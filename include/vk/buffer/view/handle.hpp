#pragma once

#include "../../handle/base.hpp"
#include "../../create_or_allocate.hpp"

#include <core/handle/declaration.hpp>

namespace vk {

	struct buffer_view;

	template<>
	inline constexpr bool is_creatable<vk::buffer_view> = true;

} // vk

template<>
struct handle<vk::buffer_view> : vk::handle_base<vk::non_dispatchable> {};