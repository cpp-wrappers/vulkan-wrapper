#pragma once

#include <integer.hpp>
#include <unicode/utf8.hpp>

namespace vk {

	struct layer_properties {
		utf8::unit name[256];
		uint32 spec_version;
		uint32 implementation_version;
		utf8::unit description[256];
	};

} // vk