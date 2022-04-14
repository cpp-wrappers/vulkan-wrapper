#pragma once

#include "../handle/base.hpp"
#include "../create_or_allocate.hpp"

#include <core/handle/declaration.hpp>

namespace vk {

	struct framebuffer;

	template<>
	inline constexpr bool is_creatable<vk::framebuffer> = true;

} // vk

template<>
struct handle<vk::framebuffer> : vk::handle_base<vk::non_dispatchable> {};