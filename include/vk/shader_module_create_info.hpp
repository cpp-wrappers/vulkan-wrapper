#pragma once

#include "headers.hpp"
#include <cstdint>
#include <core/integer.hpp>

namespace vk {

struct shader_module_create_info {
	uint_with_size_of<VkStructureType> m_type = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	const void* m_next = nullptr;
	int m_flags = 0;
	std::size_t m_code_size;
	const uint32_t* m_code;
};

} // vk

static_assert(sizeof(vk::shader_module_create_info) == sizeof(VkShaderModuleCreateInfo));