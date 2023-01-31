#pragma once

#include "limits.hpp"
#include "sparse_properties.hpp"

#include "../__instance/api_version.hpp"

namespace vk {

	enum class physical_device_type {
		other, integrated_gpu, discrete_gpu,
		virtual_gpu, cpu
	};

	struct physical_device_properties {
		vk::api_version api_version;
		uint32 driver_version;
		uint32 vendor_id;
		uint32 device_id;
		physical_device_type type;
		char name[256];
		uint8 pipeline_cache_uuid[16];
		vk::physical_device_limits limits;
		vk::physical_device_sparse_properties sparse_properties;
	};

} // vk
