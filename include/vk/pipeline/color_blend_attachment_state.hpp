#pragma once

#include <core/integer.hpp>
#include <core/flag_enum.hpp>

#include "../shared/blend_factor.hpp"
#include "../shared/blend_op.hpp"
#include "../shared/color_component.hpp"

namespace vk {

	struct pipeline_color_blend_attachment_state {
		uint32 enable_blend;
		vk::blend_factor src_color_blend_factor;
		vk::blend_factor dst_color_blend_factor;
		vk::blend_op color_blend_op;
		vk::blend_factor src_alpha_blend_factor;
		vk::blend_factor dst_alpha_blend_factor;
		vk::blend_op alpha_blend_op;
		flag_enum<vk::color_component> color_write_mask;
	};
}

static_assert(sizeof(vk::pipeline_color_blend_attachment_state) == sizeof(VkPipelineColorBlendAttachmentState));