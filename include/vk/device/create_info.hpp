#pragma once

#include "queue_create_info.hpp"

#include "../physical_device/features.hpp"
#include "../extension_name.hpp"

#include <core/c_string.hpp>

namespace vk {

	struct device_create_info {
		uint32 structure_type = 3;
		const void* next = nullptr;
		uint32 flags = 0;
		uint32 queue_create_info_count = 0;
		const vk::queue_create_info* queue_create_infos = nullptr;
		uint32 enabled_layer_count = 0;
		const c_string* enabled_layer_names = nullptr;
		uint32 enabled_extension_count = 0;
		const vk::extension_name* enabled_extension_names = nullptr;
		const vk::physical_device_features* enabled_features = nullptr;
	};

} // vk