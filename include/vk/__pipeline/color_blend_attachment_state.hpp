#pragma once

#include "../__internal/blend_factor.hpp"
#include "../__internal/blend_op.hpp"
#include "../__internal/color_component.hpp"

#include <enum_flags.hpp>
#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct enable_blend { uint32 _; };

	struct pipeline_color_blend_attachment_state {
		vk::enable_blend           enable_blend;
		vk::src_color_blend_factor src_color_blend_factor{};
		vk::dst_color_blend_factor dst_color_blend_factor{};
		vk::color_blend_op         color_blend_op{};
		vk::src_alpha_blend_factor src_alpha_blend_factor{};
		vk::dst_alpha_blend_factor dst_alpha_blend_factor{};
		vk::alpha_blend_op         alpha_blend_op{};
		vk::color_components       color_write_mask {
			vk::color_component::r,
			vk::color_component::g,
			vk::color_component::b,
			vk::color_component::a,
		};

		pipeline_color_blend_attachment_state(vk::enable_blend enable) :
			enable_blend{ enable }
		{}

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			count_of_decayed_same_as<vk::enable_blend> == 1,
			count_of_decayed_same_as<vk::src_color_blend_factor> == 1,
			count_of_decayed_same_as<vk::dst_color_blend_factor> == 1,
			count_of_decayed_same_as<vk::color_blend_op> == 1,
			count_of_decayed_same_as<vk::src_alpha_blend_factor> == 1,
			count_of_decayed_same_as<vk::dst_alpha_blend_factor> == 1,
			count_of_decayed_same_as<vk::alpha_blend_op> == 1,
			count_of_decayed_same_as<vk::color_components> <= 1
		>
		pipeline_color_blend_attachment_state(Args&&... args) :
			enable_blend { tuple{ args... }.template
				get_decayed_same_as<vk::enable_blend>()
			},
			src_color_blend_factor { tuple{ args... }.template
				get_decayed_same_as<vk::src_color_blend_factor>()
			},
			dst_color_blend_factor { tuple{ args... }.template
				get_decayed_same_as<vk::dst_color_blend_factor>()
			},
			color_blend_op { tuple{ args... }.template
				get_decayed_same_as<vk::color_blend_op>()
			},
			src_alpha_blend_factor { tuple{ args... }.template
				get_decayed_same_as<vk::src_alpha_blend_factor>()
			},
			dst_alpha_blend_factor { tuple{ args... }.template
				get_decayed_same_as<vk::dst_alpha_blend_factor>()
			},
			alpha_blend_op { tuple{ args... }.template
				get_decayed_same_as<vk::alpha_blend_op>()
			}
		{
			if constexpr (types<Args...>::template
				count_of_decayed_same_as<vk::color_components> > 0
			) {
				color_write_mask = tuple{ args... }.template
					get_decayed_same_as<vk::color_components>();
			}
		} // constructor

	}; // pipeline_color_blend_attachment_state

} // vk