#pragma once

#include <core/integer.hpp>

namespace vk {

	struct count {
		uint32 _;

		operator uint32 () const { return _; }
	};

} // vk