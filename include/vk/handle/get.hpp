#pragma once

#include "some_handle.hpp"
#include "some_guarded_handle.hpp"

namespace vk {

	decltype(auto) get_handle(type::vk::some_handle auto&& handle) {
		return handle;
	}

	decltype(auto) get_handle(type::vk::some_guarded_handle auto& guarded_handle) {
		return guarded_handle.handle();
	}

} // vk