#pragma once

#include <core/elements/one_of.hpp>

#include "handle.hpp"
#include "../../shared/result.hpp"
#include "../../shared/headers.hpp"

namespace vk {

	template<typename... Args>
	elements::one_of<vk::result, vk::debug_error_callback>
	try_create_debug_error_callback(Args... args) {
		// TODO
	};

}