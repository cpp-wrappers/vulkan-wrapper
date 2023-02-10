#pragma once

#include "../__internal/object_type.hpp"

#include <integer.hpp>

namespace vk::debug_utils {

	struct object_tag_info {
		uint32 type = 1000128001;
		const void* next = nullptr;
		vk::object_type object_type;
		uint64 object_handle;
		uint64 tag_name;
		nuint tag_size;
		const void* tag;
	};

}