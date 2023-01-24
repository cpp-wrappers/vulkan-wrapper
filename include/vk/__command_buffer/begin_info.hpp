#pragma once

#include "usage.hpp"
#include "inheritance_info.hpp"

namespace vk {

	struct command_buffer_begin_info {
		uint32                                     structure_type = 42;
		const void*                                next = nullptr;
		vk::command_buffer_usages                  usages;
		const vk::command_buffer_inheritance_info* inheritance_info;
	};

} // vk