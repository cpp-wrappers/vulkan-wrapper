#pragma once

#include "../../headers.hpp"
#include <core/integer.hpp>
#include <core/wrapper/of_pointer_to.hpp>
#include <core/wrapper/of_integer.hpp>

namespace vk {

	struct code_size : wrapper::of_integer<nuint, struct code_size_t> {};
	struct code : wrapper::of_pointer_to<const uint32_t>{};

	struct shader_module_create_info {
		const uint32 type = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		const void* const next;
		uint32 flags;
		vk::code_size code_size;
		vk::code code;
	};

} // vk

static_assert(sizeof(vk::shader_module_create_info) == sizeof(VkShaderModuleCreateInfo));