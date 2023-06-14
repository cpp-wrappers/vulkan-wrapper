#pragma once

#include <c_string.hpp>

#include <unicode/utf8.hpp>

namespace vk {

	struct layer_name : c_string_of_unknown_size<utf8::unit> {};

} // vk