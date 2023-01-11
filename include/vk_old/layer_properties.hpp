#pragma once

#include <core/integer.hpp>

namespace vk {

	struct layer_properties {
		char name[256];
		uint32 spec_version;
		uint32 implementation_version;
		char description[256];
	};

} // vk