#pragma once

#include "headers.hpp"
#include <core/flag_enum.hpp>
#include <vulkan/vulkan_core.h>
#include "pipeline_bind_point.hpp"
#include "attachment_reference.hpp"

namespace vk {

enum class subpass_description_flag {
	per_view_attributes = VK_SUBPASS_DESCRIPTION_PER_VIEW_ATTRIBUTES_BIT_NVX,
	per_view_position_x_only = VK_SUBPASS_DESCRIPTION_PER_VIEW_POSITION_X_ONLY_BIT_NVX,
	fragment_region = VK_SUBPASS_DESCRIPTION_FRAGMENT_REGION_BIT_QCOM,
	shader_resolve = VK_SUBPASS_DESCRIPTION_SHADER_RESOLVE_BIT_QCOM
};

struct subpass_description {
	flag_enum<subpass_description_flag> flags;
	vk::pipeline_bind_point pipeline_bind_point;
	uint32_t input_attachment_count;
	const vk::attachment_reference* input_attachments;
	uint32_t color_attachment_count;
	const vk::attachment_reference* color_attachments;
	const vk::attachment_reference* resolve_attachments;
	const vk::attachment_reference* depth_stencil_attachments;
	uint32_t preserve_attachment_count;
	const uint32_t* preserve_attachments;
};

}

static_assert(sizeof(vk::subpass_description) == sizeof(VkSubpassDescription));