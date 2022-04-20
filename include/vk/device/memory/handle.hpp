#pragma once

#include "../../handle/base.hpp"
#include "../../create_or_allocate.hpp"

#include <core/handle.hpp>

namespace vk {

	struct device_memory;

	template<>
	inline constexpr bool is_allocatable<vk::device_memory> = true;

} // vk

template<>
struct handle<vk::device_memory> : vk::handle_base<vk::non_dispatchable> {};