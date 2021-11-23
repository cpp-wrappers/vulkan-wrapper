#pragma once

#include <core/integer.hpp>
#include <core/elements/one_of.hpp>

#include "../../shared/result.hpp"

namespace vk {

	class device;

	struct command_pool {
		uint64 handle;
	}; // command_pool
} // vk