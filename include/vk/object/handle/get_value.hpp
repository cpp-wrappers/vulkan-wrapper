#pragma once

#include "get.hpp"

namespace vk {

	auto get_handle_value(vk::some_possibly_guarded_handle auto& handle) {
		return get_handle(handle).value;
	}

} // vk