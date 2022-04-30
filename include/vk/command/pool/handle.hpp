#pragma once

#include "../../handle/base.hpp"
#include "../../result.hpp"
#include "../../command/buffer/level.hpp"
#include "../../create_or_allocate.hpp"

#include <core/range_of_value_type_same_as.hpp>
#include <core/handle.hpp>

namespace vk {

	struct command_buffer;
	struct device;

	struct command_pool;

	template<>
	constexpr inline bool is_creatable<vk::command_pool> = true;

} // vk

template<>
struct handle<vk::command_pool> : vk::handle_base<vk::non_dispatchable> {
};