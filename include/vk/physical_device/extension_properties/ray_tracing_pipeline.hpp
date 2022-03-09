#pragma once

#include "vk/physical_device/extension_properties.hpp"
#include "vk/headers.hpp"

namespace vk {

	struct physical_device_ray_tracing_pipeline_properties : vk::extension_properties_marker {
		const uint32 __type = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_PROPERTIES_KHR;
		const void* next;
		uint32 shader_group_handle_size;
		uint32 max_ray_recursion_depth;
		uint32 max_shader_group_stride;
		uint32 shader_group_base_alignment;
		uint32 shader_group_handle_capture_replay_size;
		uint32 max_ray_dispatch_invocation_count;
		uint32 shader_group_handle_alignment;
		uint32 max_ray_hit_attribute_size;
	};

} // vk

static_assert(sizeof(vk::physical_device_ray_tracing_pipeline_properties) == sizeof(VkPhysicalDeviceRayTracingPipelinePropertiesKHR));