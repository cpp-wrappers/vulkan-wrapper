#pragma once

#include "headers.hpp"
#include <cxx_util/int_with_size.hpp>
#include "application_info.hpp"
#include <cxx_util/named.hpp>

namespace vk {

struct enabled_layer_name : u::named<const char*> {};

struct instance_create_info {
	u::int_with_size_of<VkStructureType> m_type = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	const void* m_next = nullptr;
	uint32_t m_flags = 0;
	vk::application_info* m_application_info = nullptr;
	uint32_t m_enabled_layer_count = 0;
	const enabled_layer_name* m_enabled_layer_names = nullptr;
	uint32_t m_enabled_extension_count = 0;
	const char* const* m_enabled_extension_names = nullptr;
};

} // vk

static_assert(sizeof(vk::instance_create_info) == sizeof(VkInstanceCreateInfo));