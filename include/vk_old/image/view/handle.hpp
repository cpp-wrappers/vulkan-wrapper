#pragma once

#include "../../handle/base.hpp"
#include "../../create_or_allocate.hpp"

#include <core/handle.hpp>

namespace vk {

	struct image_view;

	template<>
	inline constexpr bool is_creatable<vk::image_view> = true;

} // vk

template<>
struct handle<vk::image_view> : vk::handle_base<vk::non_dispatchable> {};