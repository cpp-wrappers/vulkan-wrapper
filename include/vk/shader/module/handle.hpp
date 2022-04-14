#pragma once

#include "../../handle/base.hpp"
#include "../../create_or_allocate.hpp"

#include <core/handle/declaration.hpp>

namespace vk {

	struct shader_module;

	template<>
	inline constexpr bool is_creatable<vk::shader_module> = true;

} // vk

template<>
struct handle<vk::shader_module> : vk::handle_base<vk::non_dispatchable> {};