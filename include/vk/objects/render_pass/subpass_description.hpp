#pragma once

#include "attachment_reference.hpp"
#include "../pipeline/bind_point.hpp"
#include "../../shared/headers.hpp"

#include <core/flag_enum.hpp>
#include <core/wrapper/of_integer.hpp>
#include <core/wrapper/of_pointer_to.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>
#include <core/meta/types/are_contain_range_of_value_type.hpp>
#include <core/meta/elements/range_of_value_type.hpp>

namespace vk {

	enum class subpass_description_flag {
		per_view_attributes = VK_SUBPASS_DESCRIPTION_PER_VIEW_ATTRIBUTES_BIT_NVX,
		per_view_position_x_only = VK_SUBPASS_DESCRIPTION_PER_VIEW_POSITION_X_ONLY_BIT_NVX,
		fragment_region = VK_SUBPASS_DESCRIPTION_FRAGMENT_REGION_BIT_QCOM,
		shader_resolve = VK_SUBPASS_DESCRIPTION_SHADER_RESOLVE_BIT_QCOM
	};

	struct input_attachment_reference : attachment_reference {};
	struct color_attachment_reference : attachment_reference {};
	struct resolve_attachment_reference : attachment_reference {};
	struct depth_stencil_attachment_reference : attachment_reference {};
	struct preserve_attachment_reference : attachment_reference {};

	struct subpass_description {
		flag_enum<vk::subpass_description_flag> flags;
		vk::pipeline_bind_point pipeline_bind_point{ vk::pipeline_bind_point::graphics };
		uint32 input_attachment_count = 0;
		const vk::input_attachment_reference* input_attachments = nullptr;
		uint32 color_attachment_count = 0;
		const vk::color_attachment_reference* color_attachments = nullptr;
		const vk::resolve_attachment_reference* resolve_attachments = nullptr;
		const vk::depth_stencil_attachment_reference* depth_stencil_attachments = nullptr;
		uint32 preserve_attachment_count = 0;
		const vk::preserve_attachment_reference* preserve_attachments = nullptr;
	
		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::are_may_contain_one_range_of_value_type<vk::input_attachment_reference>,
			types::are_may_contain_one_range_of_value_type<vk::color_attachment_reference>,
			types::are_may_contain_one_range_of_value_type<vk::resolve_attachment_reference>,
			types::are_may_contain_one_range_of_value_type<vk::depth_stencil_attachment_reference>,
			types::are_may_contain_one_range_of_value_type<vk::preserve_attachment_reference>
		>::for_types<Args...>
		subpass_description(Args&... args) {
	
			if constexpr(types::count_of_ranges_of_value_type<vk::input_attachment_reference>::for_types<Args...> == 1) {
				auto& input = elements::range_of_value_type<vk::input_attachment_reference>(args...);
				input_attachment_count = (uint32) input.size();
				input_attachments = input.data();
			}

			if constexpr(types::count_of_ranges_of_value_type<vk::color_attachment_reference>::for_types<Args...> == 1) {
				auto& color = elements::range_of_value_type<vk::color_attachment_reference>(args...);
				color_attachment_count = (uint32) color.size();
				color_attachments = color.data();
			}

			if constexpr(types::count_of_ranges_of_value_type<vk::resolve_attachment_reference>::for_types<Args...> == 1) {
				auto& resolve = elements::range_of_value_type<vk::resolve_attachment_reference>(args...);
				resolve_attachments = resolve.data();
			}

			if constexpr(types::count_of_ranges_of_value_type<vk::depth_stencil_attachment_reference>::for_types<Args...> == 1) {
				auto& depth_stencil = elements::range_of_value_type<vk::depth_stencil_attachment_reference>(args...);
				depth_stencil_attachments = depth_stencil.data();
			}

			if constexpr(types::count_of_ranges_of_value_type<vk::preserve_attachment_reference>::for_types<Args...> == 1) {
				auto& preserve = elements::range_of_value_type<vk::preserve_attachment_reference>(args...);
				preserve_attachment_count = (uint32) preserve.size();
				preserve_attachments = preserve.data();
			}
		}

	};

} // vk

static_assert(sizeof(vk::subpass_description) == sizeof(VkSubpassDescription));