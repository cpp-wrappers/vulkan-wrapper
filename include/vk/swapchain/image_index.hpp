#pragma once

#include <core/integer.hpp>

namespace vk {

	struct image_index {
		uint32 _;

		operator uint32 () const { return _; }
	};
	
} // vk