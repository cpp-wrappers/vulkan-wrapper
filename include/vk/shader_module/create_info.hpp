#pragma once

#include "../headers.hpp"
#include <core/integer.hpp>
#include <core/pointer.hpp>

namespace vk {

struct code_size : uint {};
struct code : pointer_of<const uint32_t>{};

struct shader_module_create_info {
	uint32 type = (primitive::uint32) VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	const void* next{};
	uint32 flags{};
	vk::code_size code_size;
	vk::code code;
};

} // vk

static_assert(sizeof(vk::shader_module_create_info) == sizeof(VkShaderModuleCreateInfo));