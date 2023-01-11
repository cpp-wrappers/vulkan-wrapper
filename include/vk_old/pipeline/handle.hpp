#pragma once

#include "../handle/base.hpp"
#include "../create_or_allocate.hpp"

#include <core/handle.hpp>

namespace vk {

	struct pipeline;

	template<>
	inline constexpr bool is_creatable<vk::pipeline> = true;

} // vk

template<>
struct handle<vk::pipeline> : vk::handle_base<vk::non_dispatchable> {};