#pragma once

#include "application_info.hpp"
#include "../shared/extension_name.hpp"
#include "../shared/headers.hpp"

namespace vk {

	struct layer_name : c_string {};
	
	struct instance_create_info {
		const uint32 type = (uint32) VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		const void* next = nullptr;
		uint32 flags;
		vk::application_info* application_info = nullptr;
		uint32 enabled_layer_count;
		const vk::layer_name* enabled_layer_names = nullptr;
		uint32 enabled_extension_count;
		const vk::extension_name* enabled_extension_names = nullptr;
	};
	
	} // vk

static_assert(sizeof(vk::instance_create_info) == sizeof(VkInstanceCreateInfo));