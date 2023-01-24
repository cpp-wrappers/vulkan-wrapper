#pragma once

#include "../__internal/viewport.hpp"
#include "../__internal/rect2d.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct viewport_count { uint32 _; };
	struct scissor_count  { uint32 _; };

	using scissor = vk::rect2d;

	struct pipeline_viewport_state_create_info {
		uint32              structure_type = 22;
		const void*         next = nullptr;
		uint32              flags = 0;
		vk::viewport_count  viewport_count{ 0 };
		const vk::viewport* viewports = nullptr;
		vk::scissor_count   scissor_count{ 0 };
		const vk::scissor*  scissors = nullptr;

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			count_of_decayed_same_as<vk::viewport_count> <= 1,
			count_of_decayed_same_as<vk::scissor_count> <= 1,
			count_of_range_of_decayed<vk::viewport> <= 1,
			count_of_range_of_decayed<vk::scissor> <= 1
		> &&
		(
			(
				types<Args...>::template
					count_of_range_of_decayed<vk::viewport> == 0 ||
				types<Args...>::template
					count_of_decayed_same_as<vk::viewport_count> == 0
			) && (
				types<Args...>::template
					count_of_range_of_decayed<vk::scissor> == 0 ||
				types<Args...>::template
					count_of_decayed_same_as<vk::scissor_count> == 0
			)
		)
		pipeline_viewport_state_create_info(Args&&... args) {
			tuple a{ args... };
			if constexpr (types<Args...>::template
				count_of_decayed_same_as<vk::viewport_count> > 0
			) {
				viewport_count = a.template
					get_decayed_same_as<vk::viewport_count>();
			}

			if constexpr (types<Args...>::template
				count_of_decayed_same_as<vk::scissor_count> > 0
			) {
				scissor_count = a.template
					get_decayed_same_as<vk::scissor_count>();
			}

			if constexpr (types<Args...>::template
				count_of_range_of_decayed<vk::viewport> > 0
			) {
				auto& viewports0 = a.template
					get_range_of_decayed<vk::viewport>();
				viewport_count = { (uint32) viewports0.size() };
				viewports = viewports0.iterator();
			}

			if constexpr (types<Args...>::template
				count_of_range_of_decayed<vk::scissor> > 0
			) {
				auto& viewports0 = a.template
					get_range_of_decayed<vk::scissor>();
				scissor_count = { (uint32) viewports0.size() };
				scissors = viewports0.iterator();
			}

		} // constructor

	}; // pipeline_viewport_state_create_info

} // vk