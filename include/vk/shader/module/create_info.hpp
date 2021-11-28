#pragma once

#include <core/integer.hpp>
#include <core/wrapper/of_pointer_to.hpp>
#include <core/wrapper/of_integer.hpp>
#include "../../shared/headers.hpp"

namespace vk {

	struct code_size : wrapper::of_integer<nuint> {};
	struct code : wrapper::of_pointer_to<const uint32_t>{};

	struct shader_module_create_info {
		uint32 type = (uint32) VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		const void* next{};
		uint32 flags{};
		vk::code_size code_size;
		vk::code code;
	};

} // vk

static_assert(sizeof(vk::shader_module_create_info) == sizeof(VkShaderModuleCreateInfo));