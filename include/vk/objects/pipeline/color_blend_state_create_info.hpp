#pragma once

#include "color_blend_attachment_state.hpp"
#include "../../shared/headers.hpp"
#include "../../shared/logic_op.hpp"

#include <core/wrapper/of.hpp>
#include <core/array.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>
#include <core/meta/types/are_contain_range_of_value_type.hpp>
#include <core/meta/elements/range_of_value_type.hpp>

namespace vk {

	struct enable_logic_op : wrapper::of<uint32, struct enable_logic_op_t> {};
	struct blend_constants : wrapper::of<array<float, 4>, struct blend_constants_t> {};

	struct pipeline_color_blend_state_create_info {
		const uint32 type = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		const void* const next{};
		const uint32 flags{};
		vk::enable_logic_op enable_logic_op{};
		vk::logic_op logic_op{};
		uint32 attachment_count{};
		const pipeline_color_blend_attachment_state* attachments{};
		vk::blend_constants blend_constants{};

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::are_may_contain_one_decayed_same_as<vk::enable_logic_op>,
			types::are_may_contain_one_decayed_same_as<vk::logic_op>,
			types::are_may_contain_one_range_of_value_type<vk::pipeline_color_blend_attachment_state>,
			types::are_may_contain_one_decayed_same_as<vk::blend_constants>
		>::for_types<Args...>
		pipeline_color_blend_state_create_info(Args&&... args) {
			if constexpr(types::are_contain_decayed_same_as<vk::enable_logic_op>::for_types<Args...>) {
				enable_logic_op = elements::decayed_same_as<vk::enable_logic_op>(args...);
			}
			if constexpr(types::are_contain_decayed_same_as<vk::logic_op>::for_types<Args...>) {
				logic_op = elements::decayed_same_as<vk::logic_op>(args...);
			}
			if constexpr(types::are_contain_decayed_same_as<vk::blend_constants>::for_types<Args...>) {
				blend_constants = elements::decayed_same_as<vk::blend_constants>(args...);
			}
			if constexpr(types::are_contain_range_of_value_type<vk::pipeline_color_blend_attachment_state>::for_types<Args...>) {
				auto& attachments0 = elements::range_of_value_type<vk::pipeline_color_blend_attachment_state>(args...);
				attachment_count = (uint32) attachments0.size();
				attachments = attachments0.data();
			}
		}
	};

} // vk

static_assert(sizeof(vk::pipeline_color_blend_state_create_info) == sizeof(VkPipelineColorBlendStateCreateInfo));