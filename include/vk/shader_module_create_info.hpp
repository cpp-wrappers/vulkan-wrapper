#pragma once

#include "headers.hpp"
#include <cstdint>
#include <core/integer.hpp>
#include <core/named.hpp>

namespace vk {

struct code_size : named<std::size_t>{};
struct code : named<const uint32_t*>{};

struct shader_module_create_info {
	uint_with_size_of<VkStructureType> type = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	const void* next = nullptr;
	int flags = 0;
	vk::code_size code_size;
	vk::code code;
};

} // vk

static_assert(sizeof(vk::shader_module_create_info) == sizeof(VkShaderModuleCreateInfo));