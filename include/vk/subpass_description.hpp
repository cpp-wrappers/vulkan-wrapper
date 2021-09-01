#pragma once

#include "headers.hpp"
#include <core/flag_enum.hpp>
#include "pipeline_bind_point.hpp"

namespace vk {

enum class subpass_description_flag {
	per_view_attributes = VK_SUBPASS_DESCRIPTION_PER_VIEW_ATTRIBUTES_BIT_NVX,
	per_view_position_x_only = VK_SUBPASS_DESCRIPTION_PER_VIEW_POSITION_X_ONLY_BIT_NVX,
	fragment_region = VK_SUBPASS_DESCRIPTION_FRAGMENT_REGION_BIT_QCOM,
	shader_resolve = VK_SUBPASS_DESCRIPTION_SHADER_RESOLVE_BIT_QCOM
};

struct subpass_description {
	flag_enum<subpass_description_flag> m_flags;
	vk::pipeline_bind_point m_pipeline_bind_point;
	// TODO
};

}