#pragma once

#include <core/meta/decayed_same_as.hpp>
#include <core/range/of_value_type_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

#include "vk/viewport.hpp"
#include "vk/rect2d.hpp"

namespace vk {

	struct viewport_count { uint32 _; };
	struct scissor_count { uint32 _; };

	using scissor = vk::rect2d;

	struct pipeline_viewport_state_create_info {
		uint32 structure_type = 22;
		const void* next = nullptr;
		uint32 flags = 0;
		vk::viewport_count viewport_count{ 0 };
		const vk::viewport* viewports = nullptr;
		vk::scissor_count scissor_count{ 0 };
		const vk::scissor* scissors = nullptr;

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_may_contain_decayed<vk::viewport_count>,
			types::are_may_contain_decayed<vk::scissor_count>,
			types::are_may_contain_range_of<vk::viewport>,
			types::are_may_contain_range_of<vk::scissor>
		>::for_types<Args...> &&
		(
			(
				!types::are_contain_range_of<vk::viewport>::for_types<Args...>
				|| !types::are_contain_decayed<
					vk::viewport_count
				>::for_types<Args...>
			) && (
				!types::are_contain_range_of<vk::scissor>::for_types<Args...>
				|| !types::are_contain_decayed<
					vk::scissor_count
				>::for_types<Args...>
			)
		)
		pipeline_viewport_state_create_info(Args&&... args) {
			if constexpr (
				types::are_contain_decayed<
					vk::viewport_count
				>::for_types<Args...>
			) {
				viewport_count = elements::decayed<vk::viewport_count>(args...);
			}

			if constexpr (
				types::are_contain_decayed<
					vk::scissor_count
				>::for_types<Args...>
			) {
				scissor_count = elements::decayed<vk::scissor_count>(args...);
			}

			if constexpr (
				types::are_contain_range_of<vk::viewport>::for_types<Args...>
			) {
				auto& viewports0 = elements::range_of<vk::viewport>(args...);
				viewport_count = { (uint32) viewports0.size() };
				viewports = viewports0.data();
			}
			if constexpr (
				types::are_contain_range_of<vk::scissor>::for_types<Args...>
			) {
				auto& scissors0 = elements::range_of<vk::scissor>(args...);
				scissor_count = { (uint32) scissors0.size() };
				scissors = scissors0.data();
			}

		} // constructor

	}; // pipeline_viewport_state_create_info

} // vk