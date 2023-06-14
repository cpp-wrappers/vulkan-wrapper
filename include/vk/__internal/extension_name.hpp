#pragma once

#include <c_string.hpp>

#include <unicode/utf8.hpp>

namespace vk {

	struct extension_name : c_string_of_unknown_size<utf8::unit> {
		extension_name() : c_string_of_unknown_size<utf8::unit>(nullptr) {};
		using c_string_of_unknown_size<utf8::unit>::c_string;
	};

} // vk