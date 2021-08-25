#pragma once

#include "headers.hpp"
#include <cxx_util/int_with_size.hpp>
#include "application_info.hpp"
#include <cxx_util/named.hpp>

namespace vk {

struct enabled_layer_name : u::named<const char*> {};
struct enabled_extension_name : u::named<const char*> {};

struct instance_create_info {
	u::int_with_size_of<VkStructureType> type = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	const void* next = nullptr;
	uint32_t flags = 0;
	vk::application_info* application_info = nullptr;
	uint32_t enabled_layer_count = 0;
	const vk::enabled_layer_name* enabled_layer_names = nullptr;
	uint32_t enabled_extension_count = 0;
	const vk::enabled_extension_name* enabled_extension_names = nullptr;
};

} // vk

static_assert(sizeof(vk::instance_create_info) == sizeof(VkInstanceCreateInfo));