#pragma once

#include "../__internal/object_type.hpp"

#include <integer.hpp>
#include <c_string.hpp>

#include <unicode/utf8.hpp>

namespace vk::debug_utils {

	struct object_name : c_string_of_unknown_size<utf8::unit> {};

	struct object_name_info {
		uint32 type = 1000128000;
		const void* next = nullptr;
		vk::object_type object_type;
		uint64 object_handle;
		vk::debug_utils::object_name object_name;
	};

}