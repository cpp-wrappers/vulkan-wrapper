#pragma once

#include "../../handle/base.hpp"
#include "../../create_or_allocate.hpp"

#include <core/handle/declaration.hpp>

namespace vk {

	struct descriptor_pool;

	template<>
	inline constexpr bool is_creatable<vk::descriptor_pool> = true;

} // vk

template<>
struct handle<vk::descriptor_pool> : vk::handle_base<vk::non_dispatchable> {};