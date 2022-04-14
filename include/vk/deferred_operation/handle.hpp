#pragma once

#include "../handle/base.hpp"
#include "../create_or_allocate.hpp"

#include <core/handle/declaration.hpp>

namespace vk {

	struct deferred_operation;

	template<>
	inline constexpr bool is_creatable<vk::deferred_operation> = true;

} // vk

template<>
struct handle<vk::deferred_operation> : vk::handle_base<vk::non_dispatchable> {};