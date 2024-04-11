#pragma once

#include <integer.hpp>
#include <unicode/utf8.hpp>

namespace vk {

	struct extension_properties {
		utf8::unit name[256];
		uint32 spec_version;
	};

} // vk