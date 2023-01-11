#pragma once

#include "../handle/base.hpp"
#include "../create_or_allocate.hpp"

#include <core/handle.hpp>

namespace vk {

	struct fence;

	template<>
	inline constexpr bool is_creatable<vk::fence> = true;

} // vk

template<>
struct handle<vk::fence> : vk::handle_base<vk::non_dispatchable> {};