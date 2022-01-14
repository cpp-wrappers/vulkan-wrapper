#pragma once

#include "../../../object/handle/base.hpp"
#include "../../../object/create_or_allocate.hpp"

namespace vk {

	struct device_memory;

	template<>
	inline constexpr bool is_allocatable<vk::device_memory> = true;

	template<>
	struct vk::handle<vk::device_memory> : vk::handle_base<vk::non_dispatchable> {};

} // vk