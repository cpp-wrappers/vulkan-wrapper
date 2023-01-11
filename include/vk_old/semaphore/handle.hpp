#pragma once

#include "../handle/base.hpp"
#include "../create_or_allocate.hpp"

#include <core/handle.hpp>

namespace vk {

	struct semaphore;

	template<>
	inline constexpr bool is_creatable<vk::semaphore> = true;

} // vk

template<>
struct handle<vk::semaphore> : vk::handle_base<vk::non_dispatchable> {};