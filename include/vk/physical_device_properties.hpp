export module vk.physical_device_properties;

export import <cinttypes>;
export import vk.api_version;
export import vk.physical_device_limits;
export import vk.physical_device_sparse_properties;

import vk_headers;

export namespace vk {

enum class physical_device_type {
	other = VK_PHYSICAL_DEVICE_TYPE_OTHER,
	integrated_gpu = VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU,
	discrete_gpu = VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU,
	virtual_gpu = VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU,
	cpu = VK_PHYSICAL_DEVICE_TYPE_CPU
};

struct physical_device_properties {
	vk::api_version api_version;
	uint32_t driver_version;
	uint32_t vendor_id;
	uint32_t device_id;
	physical_device_type type;
	char name[VK_MAX_PHYSICAL_DEVICE_NAME_SIZE];
	uint8_t pipeline_cache_uuid[VK_UUID_SIZE];
	vk::physical_device_limits limits;
	vk::physical_device_sparse_properties sparse_properties;
};

}

static_assert(
	sizeof(vk::physical_device_type)
	==
	sizeof(VkPhysicalDeviceType)
);

static_assert(
	sizeof(vk::physical_device_properties)
	==
	sizeof(VkPhysicalDeviceProperties)
);
