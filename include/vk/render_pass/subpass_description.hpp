#pragma once

#include "attachment_reference.hpp"
#include "../pipeline/bind_point.hpp"

#include <core/flag_enum.hpp>
#include <core/wrapper/of_integer.hpp>
#include <core/wrapper/of_pointer_to.hpp>
#include <core/range/of_value_type_same_as.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

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
		flag_enum<vk::subpass_description_flag> flags;
		vk::pipeline_bind_point pipeline_bind_point{
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
		requires types::are_exclusively_satisfying_predicates<
			types::are_may_contain_range_of<vk::input_attachment_reference>,
			types::are_may_contain_range_of<vk::color_attachment_reference>,
			types::are_may_contain_range_of<vk::resolve_attachment_reference>,
			types::are_may_contain_range_of<
				vk::depth_stencil_attachment_reference
			>,
			types::are_may_contain_range_of<vk::preserve_attachment_reference>
		>::for_types<Args...>
		subpass_description(Args&... args) {
			if constexpr(
				types::are_contain_range_of<
					vk::input_attachment_reference
				>::for_types<Args...>
			) {
				auto& input = elements::range_of<
					vk::input_attachment_reference
				>(args...);
				input_attachment_count = (uint32) input.size();
				input_attachments = input.data();
			}

			if constexpr(
				types::are_contain_range_of<
					vk::color_attachment_reference
				>::for_types<Args...>
			) {
				auto& color = elements::range_of<
					vk::color_attachment_reference
				>(args...);
				color_attachment_count = (uint32) color.size();
				color_attachments = color.data();
			}

			if constexpr(
				types::are_contain_range_of<
					vk::resolve_attachment_reference
				>::for_types<Args...>
			) {
				auto& resolve = elements::range_of<
					vk::resolve_attachment_reference
				>(args...);
				resolve_attachments = resolve.data();
			}

			if constexpr(
				types::are_contain_range_of<
					vk::depth_stencil_attachment_reference
				>::for_types<Args...>
			) {
				auto& depth_stencil = elements::range_of<
					vk::depth_stencil_attachment_reference
				>(args...);
				depth_stencil_attachments = depth_stencil.data();
			}

			if constexpr(
				types::are_contain_range_of<
					vk::preserve_attachment_reference
				>::for_types<Args...>
			) {
				auto& preserve = elements::range_of<
					vk::preserve_attachment_reference
				>(args...);
				preserve_attachment_count = (uint32) preserve.size();
				preserve_attachments = preserve.data();
			}
		}

	}; // subpass_description

} // vk