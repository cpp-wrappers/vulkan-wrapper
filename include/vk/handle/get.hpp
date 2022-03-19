#pragma once

#include <core/handle/some.hpp>
#include <core/handle/some_guarded.hpp>

namespace vk {

	decltype(auto) get_handle(some_handle auto&& handle) {
		return handle;
	}

	decltype(auto) get_handle(some_guarded_handle auto& guarded_handle) {
		return guarded_handle.handle();
	}

} // vk