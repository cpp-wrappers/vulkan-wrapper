#pragma once

#include <core/integer.hpp>

namespace vk {

	struct extension_properties {
		char name[256];
		uint32 spec_version;
	};

} // vk