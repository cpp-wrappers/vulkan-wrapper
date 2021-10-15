#pragma once

#include <core/flag_enum.hpp>

#include "../../descriptor_set_layout/descriptor_set_layout.hpp"
#include "../../headers.hpp"
#include "../push_constant_range.hpp"

namespace vk {

struct pipeline_layout_create_info {
	uint32 type = (primitive::uint32) VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	const void* next{};
	uint32 flags{};
	uint32 descriptor_set_layout_count{};
	const vk::descriptor_set_layout* descriptor_set_layouts{};
	uint32 push_constant_range_count{};
	const vk::push_constant_range* push_constant_ranges{};
}; // pipeline_layout_create_info

} // vk

static_assert(sizeof(vk::pipeline_layout_create_info) == sizeof(VkPipelineLayoutCreateInfo));