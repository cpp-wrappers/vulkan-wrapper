#pragma once

#include "queue_create_info.hpp"

#include <core/c_string.hpp>

#include "vk/physical_device/features.hpp"
#include "vk/headers.hpp"
#include "vk/extension_name.hpp"

namespace vk {

	struct device_create_info {
		const uint32 type = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		const void* next;
		uint32 flags;
		uint32 queue_create_info_count;
		const vk::queue_create_info* queue_create_infos;
		uint32 enabled_layer_count;
		const c_string* enabled_layer_names;
		uint32 enabled_extension_count;
		const vk::extension_name* enabled_extension_names;
		const vk::physical_device_features* enabled_features;
	};

} // vk

static_assert(sizeof(vk::device_create_info) == sizeof(VkDeviceCreateInfo));