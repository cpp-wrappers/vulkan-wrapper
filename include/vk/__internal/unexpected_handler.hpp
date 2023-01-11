#pragma once

#ifndef VK_UNEXPECTED_HANDLER_HEADER

#include "./result.hpp"

namespace vk {

	[[ noreturn ]]
	void unexpected_handler();

	[[ noreturn ]]
	void unexpected_handler(vk::result);

} // vk

#else

#include_next VK_UNEXPECTED_HANDLER_HEADER

#endif