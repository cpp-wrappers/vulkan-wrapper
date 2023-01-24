#pragma once

#include "./attachment_reference.hpp"
#include "../__pipeline/bind_point.hpp"

#include <enum_flags.hpp>
#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	enum class subpass_description_flag {
		per_view_attributes      = 0x00000001,
		per_view_position_x_only = 0x00000002,
		fragment_region          = 0x00000004,
		shader_resolve           = 0x00000008
	};

	struct input_attachment_reference : attachment_reference {};
	struct color_attachment_reference : attachment_reference {};
	struct resolve_attachment_reference : attachment_reference {};
	struct depth_stencil_attachment_reference : attachment_reference {};
	struct preserve_attachment_reference : attachment_reference {};

	struct subpass_description {
		enum_flags<vk::subpass_description_flag> flags;
		vk::pipeline_bind_point pipeline_bind_point {
			vk::pipeline_bind_point::graphics
		};
		uint32 input_attachment_count = 0;
		const vk::input_attachment_reference* input_attachments = nullptr;
		uint32 color_attachment_count = 0;
		const vk::color_attachment_reference* color_attachments = nullptr;
		const vk::resolve_attachment_reference* resolve_attachments = nullptr;
		const vk::depth_stencil_attachment_reference*
			depth_stencil_attachments = nullptr;
		uint32 preserve_attachment_count = 0;
		const vk::preserve_attachment_reference* preserve_attachments = nullptr;
	
		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			count_of_range_of_decayed<vk::input_attachment_reference> <= 1,
			count_of_range_of_decayed<vk::color_attachment_reference> <= 1,
			count_of_range_of_decayed<vk::resolve_attachment_reference> <= 1,
			count_of_range_of_decayed<
				vk::depth_stencil_attachment_reference
			> <= 1,
			count_of_range_of_decayed<vk::preserve_attachment_reference> <= 1
		>
		subpass_description(Args&... args) {
			if constexpr (types<Args...>::template
				count_of_range_of_decayed<vk::input_attachment_reference> > 0
			) {
				auto& input = tuple{ args... }.template
					get_range_of_decayed<vk::input_attachment_reference>();
				input_attachment_count = (uint32) input.size();
				input_attachments = input.iterator();
			}

			if constexpr (types<Args...>::template
				count_of_range_of_decayed<vk::color_attachment_reference> > 0
			) {
				auto& color = tuple{ args... }.template
					get_range_of_decayed<vk::color_attachment_reference>();
				color_attachment_count = (uint32) color.size();
				color_attachments = color.iterator();
			}

			if constexpr (types<Args...>::template
				count_of_range_of_decayed<vk::resolve_attachment_reference> > 0
			) {
				auto& resolve = tuple{ args... }.template
					get_range_of_decayed<vk::resolve_attachment_reference>();
				input_attachments = resolve.iterator();
			}

			if constexpr (types<Args...>::template
				count_of_range_of_decayed<
					vk::depth_stencil_attachment_reference
				> > 0
			) {
				auto& depth = tuple{ args... }.template
					get_range_of_decayed<
						vk::depth_stencil_attachment_reference
					>();
				depth_stencil_attachments = depth.iterator();
			}

			if constexpr (types<Args...>::template
				count_of_range_of_decayed<vk::preserve_attachment_reference> > 0
			) {
				auto& preserve = tuple{ args... }.template
					get_range_of_decayed<vk::preserve_attachment_reference>();
				preserve_attachment_count = (uint32) preserve.size();
				preserve_attachments = preserve.iterator();
			}

		} // constructor

	}; // subpass_description

} // vk