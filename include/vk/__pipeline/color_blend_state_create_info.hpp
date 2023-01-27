#pragma once

#include "./color_blend_attachment_state.hpp"
#include "../__internal/logic_op.hpp"

#include <array.hpp>
#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct enable_logic_op { uint32 _; };
	struct blend_constants : array<float, 4> {};

	struct pipeline_color_blend_state_create_info {
		uint32              structure_type = 26;
		const void*         next = nullptr;
		const uint32        flags{};
		vk::enable_logic_op enable_logic_op{};
		vk::logic_op        logic_op{};
		uint32              attachment_count{};
		const pipeline_color_blend_attachment_state*
		                    attachments{};
		vk::blend_constants blend_constants{};

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			count_of_decayed_same_as<vk::enable_logic_op> <= 1,
			count_of_decayed_same_as<vk::logic_op> <= 1,
			count_of_range_of_decayed<
				vk::pipeline_color_blend_attachment_state
			> <= 1,
			count_of_decayed_same_as<vk::blend_constants> <= 1
		>
		pipeline_color_blend_state_create_info(Args&&... args) {
			if constexpr (types<Args...>::template
				count_of_decayed_same_as<vk::enable_logic_op> > 0
			) {
				enable_logic_op = tuple{ args... }.template
					get_decayed_same_as<vk::enable_logic_op>();
			}
			
			if constexpr (types<Args...>::template
				count_of_decayed_same_as<vk::logic_op> > 0
			) {
				logic_op = tuple{ args... }.template
					get_decayed_same_as<vk::logic_op>();
			}

			if constexpr (types<Args...>::template
				count_of_decayed_same_as<vk::blend_constants> > 0
			) {
				enable_logic_op = tuple{ args... }.template
					get_decayed_same_as<vk::blend_constants>();
			}

			if constexpr (types<Args...>::template
				count_of_range_of_decayed<
					vk::pipeline_color_blend_attachment_state
				> > 0
			) {
				auto& attachments0 = tuple{ args... }.template
					get_range_of_decayed<
						vk::pipeline_color_blend_attachment_state
					>();
				attachment_count = (uint32) attachments0.size();
				attachments = attachments0.iterator();
			}

		} // constructor

	}; // pipeline_color_blend_state_create_info

} // vk