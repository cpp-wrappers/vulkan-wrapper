#pragma once

#include <core/integer.hpp>
#include <core/wrapper/of_pointer_to.hpp>
#include <core/wrapper/of_integer.hpp>

namespace vk {

	struct code_size : wrapper::of_integer<nuint, struct code_size_t> {};
	struct code : wrapper::of_pointer_to<const uint32>{};

	struct shader_module_create_info {
		uint32 structure_type = 16;
		const void* next;
		uint32 flags;
		vk::code_size code_size;
		vk::code code;
	};

} // vk