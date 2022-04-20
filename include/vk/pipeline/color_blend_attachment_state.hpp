#pragma once

#include <core/flag_enum.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/meta/decayed_same_as.hpp>

#include "../blend_factor.hpp"
#include "../blend_op.hpp"
#include "../color_component.hpp"

namespace vk {

	struct enable_blend { uint32 _; };

	struct pipeline_color_blend_attachment_state {
		vk::enable_blend enable_blend;
		vk::src_color_blend_factor src_color_blend_factor;
		vk::dst_color_blend_factor dst_color_blend_factor;
		vk::color_blend_op color_blend_op;
		vk::src_alpha_blend_factor src_alpha_blend_factor;
		vk::dst_alpha_blend_factor dst_alpha_blend_factor;
		vk::alpha_blend_op alpha_blend_op;
		vk::color_components color_write_mask {
			vk::color_component::r,
			vk::color_component::g,
			vk::color_component::b,
			vk::color_component::a,
		};

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<vk::enable_blend>,
			types::are_contain_one_decayed<vk::src_color_blend_factor>,
			types::are_contain_one_decayed<vk::dst_color_blend_factor>,
			types::are_contain_one_decayed<vk::color_blend_op>,
			types::are_contain_one_decayed<vk::src_alpha_blend_factor>,
			types::are_contain_one_decayed<vk::dst_alpha_blend_factor>,
			types::are_contain_one_decayed<vk::alpha_blend_op>,
			types::are_may_contain_one_decayed<vk::color_components>
		>::for_types<Args...>
		pipeline_color_blend_attachment_state(Args&&... args) :
			enable_blend {
				elements::decayed<vk::enable_blend>(args...)
			},
			src_color_blend_factor {
				elements::decayed<vk::src_color_blend_factor>(args...)
			},
			dst_color_blend_factor {
				elements::decayed<vk::dst_color_blend_factor>(args...)
			},
			color_blend_op {
				elements::decayed<vk::color_blend_op>(args...)
			},
			src_alpha_blend_factor {
				elements::decayed<vk::src_alpha_blend_factor>(args...)
			},
			dst_alpha_blend_factor {
				elements::decayed<vk::dst_alpha_blend_factor>(args...)
			},
			alpha_blend_op {
				elements::decayed<vk::alpha_blend_op>(args...)
			}
		{
			if constexpr (
				types::are_contain_decayed<
					vk::color_components
				>::for_types<Args...>
			) {
				color_write_mask =
					elements::decayed<vk::color_components>(args...);
			}
		} // constructor

	}; // pipeline_color_blend_attachment_state

} // vk