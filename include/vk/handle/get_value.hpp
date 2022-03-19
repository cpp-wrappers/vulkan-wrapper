#pragma once

#include "get.hpp"

#include <core/handle/some_possibly_guarded.hpp>

namespace vk {

	auto get_handle_value(some_possibly_guarded_handle auto& handle) {
		return vk::get_handle(handle).value;
	}

} // vk