#pragma once

#include "../handle/base.hpp"
#include "../create_or_allocate.hpp"

#include <core/handle.hpp>

namespace vk {

	struct acceleration_structure;

	template<>
	inline constexpr bool is_creatable<vk::acceleration_structure> = true;

} // vk

template<>
struct handle<vk::acceleration_structure> : vk::handle_base<vk::non_dispatchable> {};