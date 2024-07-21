#pragma once

#include "./color_blend_attachment_state.hpp"
#include "../__internal/logic_op.hpp"

#include <array.hpp>
#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct enable_logic_op { uint32 _; };
	struct blend_constants : array<float, 4> {};


	struct _pipeline_color_blend_state_create_info {
		uint32              structure_type = 26;
		const void*         next = nullptr;
		uint32              flags{};
		vk::enable_logic_op enable_logic_op{};
		vk::logic_op        logic_op{};
		uint32              attachment_count{};
		const pipeline_color_blend_attachment_state*
		                    attachments{};
		vk::blend_constants blend_constants{};
	};


	struct _pipeline_color_blend_state_create_info_mark {};

	template<
		range_of_decayed<pipeline_color_blend_attachment_state> AttachementsRange
	>
	struct pipeline_color_blend_state_create_info :
		_pipeline_color_blend_state_create_info_mark
	{
		vk::enable_logic_op enable_logic_op{};
		vk::logic_op        logic_op{};
		AttachementsRange   attachments{};
		vk::blend_constants blend_constants{};

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			count_of_decayed_same_as<vk::enable_logic_op> <= 1,
			count_of_decayed_same_as<vk::logic_op> <= 1,
			count_of_decayed_same_as<AttachementsRange> <= 1,
			count_of_decayed_same_as<vk::blend_constants> <= 1
		>
		pipeline_color_blend_state_create_info(Args&&... args):
			attachments{
				tuple{forward<Args>(args)...}
				.template get_satisfying_predicate<
					is_same_as<AttachementsRange>.decayed
				>()
			}
		{
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

		} // constructor

		operator vk::_pipeline_color_blend_state_create_info () {
			vk::_pipeline_color_blend_state_create_info result{};
			result.enable_logic_op = enable_logic_op;
			result.logic_op = logic_op;
			result.attachments = attachments.iterator();
			result.attachment_count = attachments.size();
			result.blend_constants = blend_constants;
			return result;
		}

	}; // pipeline_color_blend_state_create_info


	template<typename... Args>
	pipeline_color_blend_state_create_info(Args...)
		-> pipeline_color_blend_state_create_info<
			typename types<Args...>::template get<is_range_of_decayed<pipeline_color_blend_attachment_state>>
		>;

} // vk