#pragma once

#include "color_blend_attachment_state.hpp"

#include "../logic_op.hpp"

#include <core/array.hpp>
#include <core/range/of_value_type_same_as.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

namespace vk {

	struct enable_logic_op { uint32 _; };
	struct blend_constants : array<float, 4> {};

	struct pipeline_color_blend_state_create_info {
		uint32 structure_type = 26;
		const void* next = nullptr;
		const uint32 flags{};
		vk::enable_logic_op enable_logic_op{};
		vk::logic_op logic_op{};
		uint32 attachment_count{};
		const pipeline_color_blend_attachment_state* attachments{};
		vk::blend_constants blend_constants{};

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_may_contain_one_decayed<vk::enable_logic_op>,
			types::are_may_contain_one_decayed<vk::logic_op>,
			types::are_may_contain_range_of<
				vk::pipeline_color_blend_attachment_state
			>,
			types::are_may_contain_one_decayed<vk::blend_constants>
		>::for_types<Args...>
		pipeline_color_blend_state_create_info(Args&&... args) {
			if constexpr (
				types::are_contain_decayed<
					vk::enable_logic_op
				>::for_types<Args...>
			) {
				enable_logic_op = elements::decayed<
					vk::enable_logic_op
				>(args...);
			}
			if constexpr (
				types::are_contain_decayed<vk::logic_op>::for_types<Args...>
			) { logic_op = elements::decayed<vk::logic_op>(args...); }

			if constexpr (
				types::are_contain_decayed<
					vk::blend_constants
				>::for_types<Args...>
			) {
				blend_constants = elements::decayed<
					vk::blend_constants
				>(args...);
			}
			if constexpr (
				types::are_contain_range_of<
					vk::pipeline_color_blend_attachment_state
				>::for_types<Args...>
			) {
				auto& attachments0 = elements::range_of<
					vk::pipeline_color_blend_attachment_state
				>(args...);
				attachment_count = (uint32) attachments0.size();
				attachments = attachments0.data();
			}

		} // constructor

	}; // pipeline_color_blend_state_create_info

} // vk