#pragma once

#include "../handle/base.hpp"
#include "../create_or_allocate.hpp"

#include <core/handle.hpp>

namespace vk {

	struct sampler;

	template<>
	inline constexpr bool is_creatable<vk::sampler> = true;

} // vk

template<>
struct handle<vk::sampler> : vk::handle_base<vk::non_dispatchable> {};