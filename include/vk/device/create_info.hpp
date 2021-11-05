#pragma once

#include "../shared/headers.hpp"
#include "queue_create_info.hpp"
#include "../physical_device/features.hpp"
#include "../shared/extension_name.hpp"
#include <core/integer.hpp>
#include <core/c_string.hpp>

namespace vk {

	struct device_create_info {
		uint32 type = (uint32) VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		const void* next = nullptr;
		uint32 flags = 0;
		uint32 queue_create_info_count;
		const vk::queue_create_info* queue_create_infos = nullptr;
		uint32 enabled_layer_count;
		const c_string* enabled_layer_names = nullptr;
		uint32 enabled_extension_count{};
		const vk::extension_name* enabled_extension_names{};
		const vk::physical_device_features* enabled_features = nullptr;
	}; // device_create_info

} // vk

static_assert(sizeof(vk::device_create_info) == sizeof(VkDeviceCreateInfo));