#pragma once

#include <core/integer.hpp>
#include <core/flag_enum.hpp>

#include <core/meta/types/are_exclusively_satsify_predicates.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/wrapper/of_integer.hpp>

#include "vk/blend_factor.hpp"
#include "vk/blend_op.hpp"
#include "vk/color_component.hpp"

namespace vk {

	struct enable_blend : wrapper::of_integer<uint32, struct enable_blend_t>{};

	struct pipeline_color_blend_attachment_state {
		vk::enable_blend enable_blend;
		vk::src_color_blend_factor src_color_blend_factor;
		vk::dst_color_blend_factor dst_color_blend_factor;
		vk::color_blend_op color_blend_op;
		vk::src_alpha_blend_factor src_alpha_blend_factor;
		vk::dst_alpha_blend_factor dst_alpha_blend_factor;
		vk::alpha_blend_op alpha_blend_op;
		vk::color_components color_write_mask;

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::are_contain_one_decayed_same_as<vk::enable_blend>,
			types::are_contain_one_decayed_same_as<vk::src_color_blend_factor>,
			types::are_contain_one_decayed_same_as<vk::dst_color_blend_factor>,
			types::are_contain_one_decayed_same_as<vk::color_blend_op>,
			types::are_contain_one_decayed_same_as<vk::src_alpha_blend_factor>,
			types::are_contain_one_decayed_same_as<vk::dst_alpha_blend_factor>,
			types::are_contain_one_decayed_same_as<vk::alpha_blend_op>,
			types::are_contain_one_decayed_same_as<vk::color_components>
		>::for_types<Args...>
		pipeline_color_blend_attachment_state(Args&&... args)
		:
			enable_blend{ elements::decayed_same_as<vk::enable_blend>(args...) },
			src_color_blend_factor{ elements::decayed_same_as<vk::src_color_blend_factor>(args...) },
			dst_color_blend_factor{ elements::decayed_same_as<vk::dst_color_blend_factor>(args...) },
			color_blend_op{ elements::decayed_same_as<vk::color_blend_op>(args...) },
			src_alpha_blend_factor{ elements::decayed_same_as<vk::src_alpha_blend_factor>(args...) },
			dst_alpha_blend_factor{ elements::decayed_same_as<vk::dst_alpha_blend_factor>(args...) },
			alpha_blend_op{ elements::decayed_same_as<vk::alpha_blend_op>(args...) },
			color_write_mask{ elements::decayed_same_as<vk::color_components>(args...) }
		{}

	};

} // vk

static_assert(sizeof(vk::pipeline_color_blend_attachment_state) == sizeof(VkPipelineColorBlendAttachmentState));