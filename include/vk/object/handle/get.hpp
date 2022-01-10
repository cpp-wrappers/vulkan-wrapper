#pragma once

#include "concepts.hpp"
#include "guarded/concepts.hpp"

namespace vk {

	decltype(auto) get_handle(vk::some_handle auto&& handle) {
		return handle;
	}

	decltype(auto) get_handle(vk::some_guarded_handle auto& guarded_handle) {
		return guarded_handle.handle();
	}
}