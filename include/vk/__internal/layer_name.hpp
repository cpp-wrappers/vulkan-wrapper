#pragma once

#include <c_string.hpp>

#include <unicode/utf8.hpp>

namespace vk {

	struct layer_name : c_string_of_unknown_size<utf8::unit> {
		using base_type = c_string_of_unknown_size<utf8::unit>;

		using base_type::base_type;
		layer_name() : base_type(u8"") {};
	};

} // vk