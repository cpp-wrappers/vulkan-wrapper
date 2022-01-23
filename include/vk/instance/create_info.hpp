#pragma once

#include "application_info.hpp"
#include "../extension_name.hpp"
#include "../headers.hpp"
#include "../layer_name.hpp"

namespace vk {
	
	struct instance_create_info {
		const uint32 type = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		const void* const next;
		uint32 flags;
		const vk::application_info* application_info;
		uint32 enabled_layer_count;
		const vk::layer_name* enabled_layer_names;
		uint32 enabled_extension_count;
		const vk::extension_name* enabled_extension_names;
	};
	
} // vk

static_assert(sizeof(vk::instance_create_info) == sizeof(VkInstanceCreateInfo));