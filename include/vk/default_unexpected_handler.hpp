#pragma once

#include "result.hpp"

extern "C" void abort() noexcept(true);

namespace vk {

	[[ noreturn ]]
	inline void default_unexpected_handler() {
		abort();
		__builtin_unreachable();
	}

	[[ noreturn ]]
	inline void default_unexpected_handler([[maybe_unused]] vk::result result) {
		vk::default_unexpected_handler();
	}

}