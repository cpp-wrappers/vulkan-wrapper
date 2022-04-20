#pragma once

#include "../../../handle/base.hpp"
#include "../../../create_or_allocate.hpp"

#include <core/handle.hpp>

namespace vk {

	struct debug_report_callback;

	template<>
	inline constexpr bool is_creatable<vk::debug_report_callback> = true;

} // vk

template<>
struct handle<vk::debug_report_callback> :
	vk::handle_base<vk::non_dispatchable>
{};