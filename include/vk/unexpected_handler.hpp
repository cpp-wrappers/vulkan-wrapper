#pragma once

#ifndef VK_UNEXPECTED_HANDLER_HEADER

#include "result.hpp"

namespace vk {

	[[ noreturn ]]
	inline void unexpected_handler();

	[[ noreturn ]]
	inline void unexpected_handler(vk::result result);


} // vk

#else

#include_next VK_UNEXPECTED_HANDLER_HEADER

#endif