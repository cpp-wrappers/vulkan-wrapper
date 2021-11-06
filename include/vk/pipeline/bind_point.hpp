#pragma once

#include "../shared/headers.hpp"

namespace vk {

enum class pipeline_bind_point {
	graphics = VK_PIPELINE_BIND_POINT_GRAPHICS,
	compute = VK_PIPELINE_BIND_POINT_COMPUTE,
	ray_tracing_khr = VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR,
	subpass_shading_huawei = VK_PIPELINE_BIND_POINT_SUBPASS_SHADING_HUAWEI,
	ray_tracing_nv = VK_PIPELINE_BIND_POINT_RAY_TRACING_NV
};

}