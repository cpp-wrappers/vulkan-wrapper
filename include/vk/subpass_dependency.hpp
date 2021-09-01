#pragma once

#include <cstdint>
#include "pipeline_stage_flag.hpp"
#include <core/flag_enum.hpp>
#include <vulkan/vulkan_core.h>
#include "access_flag.hpp"
#include "dependency_flag.hpp"

namespace vk {

struct subpass_dependency {
	uint32_t src_subpass;
	uint32_t dst_subpass;
	flag_enum<vk::pipeline_stage_flag> src_stages;
	flag_enum<vk::pipeline_stage_flag> dst_stages;
	flag_enum<vk::access_flag> src_access;
	flag_enum<vk::access_flag> dst_access;
	flag_enum<vk::dependency_flag> dependency_flags;
};

}

static_assert(sizeof(vk::subpass_dependency) == sizeof(VkSubpassDependency));