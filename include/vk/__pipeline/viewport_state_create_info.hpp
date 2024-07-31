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
			is_same_as<vk::viewport_count>.decayed <= 1,
			is_same_as<vk::scissor_count>.decayed <= 1,
			is_range_of<is_same_as<vk::viewport>.decayed> <= 1,
			is_range_of<is_same_as<vk::scissor>.decayed> <= 1
		> &&
		(
			(
				types<Args...>::template
				count_of<is_range_of<is_same_as<vk::viewport>.decayed>> == 0
				||
				types<Args...>::template
				count_of<is_same_as<vk::viewport_count>.decayed> == 0
			) && (
				types<Args...>::template
				count_of<is_range_of<is_same_as<vk::scissor>.decayed>> == 0
				||
				types<Args...>::template
				count_of<is_same_as<vk::scissor_count>.decayed> == 0
			)
		)
		pipeline_viewport_state_create_info(Args&&... args) {
			tuple a{ args... };
			if constexpr (
				(is_same_as<vk::viewport_count>.decayed > 0)
				.for_types<Args...>()
			) {
				viewport_count = a.template
					get<is_same_as<vk::viewport_count>.decayed>();
			}

			if constexpr (
				(is_same_as<vk::scissor_count>.decayed > 0)
				.for_types<Args...>()
			) {
				scissor_count = a.template
					get<is_same_as<vk::scissor_count>.decayed>();
			}

			if constexpr (types<Args...>::template
				count_of<is_range_of<
					is_same_as<vk::viewport>.decayed
				>> > 0
			) {
				auto& viewports0 = a.template
					get<is_range_of<is_same_as<vk::viewport>.decayed>>();
				viewport_count = { (uint32) viewports0.size() };
				viewports = viewports0.iterator();
			}

			if constexpr (types<Args...>::template
				count_of<is_range_of<
					is_same_as<vk::scissor>.decayed
				>> > 0
			) {
				auto& viewports0 = a.template
					get<is_range_of<is_same_as<vk::scissor>.decayed>>();
				scissor_count = { (uint32) viewports0.size() };
				scissors = viewports0.iterator();
			}

		} // constructor

	}; // pipeline_viewport_state_create_info

} // vk