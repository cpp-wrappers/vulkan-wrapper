#pragma once

#include "headers.hpp"
#include "device_queue_create_info.hpp"
#include "physical_device_features.hpp"
#include <core/integer.hpp>
#include <cassert>

namespace vk {

struct device_create_info {
	int_with_size_of<VkStructureType> type = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	const void* m_next = nullptr;
	int m_flags = 0;
	uint32_t m_queue_create_info_count = 0;
	const vk::device_queue_create_info* m_queue_create_infos = nullptr;
	uint32_t m_enabled_layer_count = 0;
	const char* const* m_enabled_layer_names = nullptr;
	uint32_t m_enabled_extension_count = 0;
	const char* const* m_enabled_extension_names = nullptr;
	const vk::physical_device_features* m_enabled_features = nullptr;
}; // device_create_info

} // vk

static_assert(sizeof(vk::device_create_info) == sizeof(VkDeviceCreateInfo));