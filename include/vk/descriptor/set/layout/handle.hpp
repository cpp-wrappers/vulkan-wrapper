#pragma once

#include "../../../handle/base.hpp"
#include "../../../create_or_allocate.hpp"

#include <core/handle.hpp>

namespace vk {

	struct descriptor_set_layout;

	template<>
	inline constexpr bool is_creatable<vk::descriptor_set_layout> = true;

} // vk

template<>
struct handle<vk::descriptor_set_layout> : vk::handle_base<vk::non_dispatchable> {};