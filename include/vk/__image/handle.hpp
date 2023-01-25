#pragma once

#include "../handle/base.hpp"
#include "../create_or_allocate.hpp"

#include <core/handle.hpp>

namespace vk {

	struct image;

	template<>
	inline constexpr bool is_creatable<vk::image> = true;

} // vk

template<>
struct handle<vk::image> : vk::handle_base<vk::non_dispatchable> {};