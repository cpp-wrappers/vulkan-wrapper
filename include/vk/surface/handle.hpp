#pragma once

#include "../handle/base.hpp"
#include "../create_or_allocate.hpp"

#include <core/handle/declaration.hpp>

namespace vk {

	struct surface;

	template<>
	inline constexpr bool is_creatable<vk::surface> = true;

} // vk

template<>
struct handle<vk::surface> : vk::handle_base<vk::non_dispatchable> {};