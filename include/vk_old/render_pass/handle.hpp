#pragma once

#include "../handle/base.hpp"
#include "../create_or_allocate.hpp"

#include <core/handle.hpp>

namespace vk {

	struct render_pass;

	template<>
	inline constexpr bool is_creatable<vk::render_pass> = true;

} // vk

template<>
struct handle<vk::render_pass> : vk::handle_base<vk::non_dispatchable> {};