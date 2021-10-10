#pragma once

#include "../headers.hpp"
#include "../instance/api_version.hpp"
#include "limits.hpp"
#include "sparse_properties.hpp"
#include <core/integer.hpp>

namespace vk {

enum class physical_device_type {
	other = VK_PHYSICAL_DEVICE_TYPE_OTHER,
	integrated_gpu = VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU,
	discrete_gpu = VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU,
	virtual_gpu = VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU,
	cpu = VK_PHYSICAL_DEVICE_TYPE_CPU
};

struct physical_device_properties {
	vk::api_version api_version;
	uint32 driver_version;
	uint32 vendor_id;
	uint32 device_id;
	physical_device_type type;
	char name[VK_MAX_PHYSICAL_DEVICE_NAME_SIZE];
	uint8 pipeline_cache_uuid[VK_UUID_SIZE];
	vk::physical_device_limits limits;
	vk::physical_device_sparse_properties sparse_properties;
};

}

static_assert(sizeof(vk::physical_device_type) == sizeof(VkPhysicalDeviceType));
static_assert(sizeof(vk::physical_device_properties) == sizeof(VkPhysicalDeviceProperties));
