#pragma once

#include <integer.hpp>

namespace vk {

	struct code_size { nuint _; };
	struct code { const uint32* _; };

	struct shader_module_create_info {
		uint32        structure_type = 16;
		const void*   next;
		uint32        flags;
		vk::code_size code_size;
		vk::code      code;
	};

} // vk