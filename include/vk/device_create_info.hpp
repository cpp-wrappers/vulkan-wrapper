#pragma once

#include "headers.hpp"
#include "device_queue_create_info.hpp"
#include "physical_device_features.hpp"
#include <core/integer.hpp>
#include <core/null_terminated_string_view.hpp>
#include <cassert>

namespace vk {

struct device_create_info {
	int_with_size_of<VkStructureType> type = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	const void* next = nullptr;
	int flags = 0;
	uint32_t queue_create_info_count = 0;
	const vk::device_queue_create_info* queue_create_infos = nullptr;
	uint32_t enabled_layer_count = 0;
	const null_terminated_string_view<size_is::undefined>* enabled_layer_names = nullptr;
	uint32_t enabled_extension_count = 0;
	const null_terminated_string_view<size_is::undefined>* enabled_extension_names = nullptr;
	const vk::physical_device_features* enabled_features = nullptr;
}; // device_create_info

} // vk

static_assert(sizeof(vk::device_create_info) == sizeof(VkDeviceCreateInfo));