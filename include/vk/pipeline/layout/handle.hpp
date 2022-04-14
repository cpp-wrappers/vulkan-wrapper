#pragma once

#include "../../handle/base.hpp"
#include "../../create_or_allocate.hpp"

#include <core/handle/declaration.hpp>

namespace vk {

	struct pipeline_layout;

	template<>
	inline constexpr bool is_creatable<vk::pipeline_layout> = true;

} // vk

template<>
struct handle<vk::pipeline_layout> :
	vk::handle_base<vk::non_dispatchable>
{};