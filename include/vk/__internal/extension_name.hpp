#pragma once

#include <c_string.hpp>

namespace vk {

	struct extension_name : c_string_of_unknown_size {
		extension_name() : c_string_of_unknown_size(nullptr) {};
		using c_string_of_unknown_size::c_string;
	};

} // vk