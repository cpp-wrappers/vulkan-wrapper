#pragma once

#include "get.hpp"
#include "some_possibly_guarded_handle.hpp"

namespace vk {

	auto get_handle_value(type::vk::some_possibly_guarded_handle auto& handle) {
		return get_handle(handle).value;
	}

} // vk