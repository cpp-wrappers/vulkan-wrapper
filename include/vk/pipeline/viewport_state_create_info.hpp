#pragma once

#include <core/meta/decayed_same_as.hpp>
#include <core/range/of_value_type.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

#include "vk/headers.hpp"
#include "vk/viewport.hpp"
#include "vk/rect2d.hpp"

namespace vk {

	struct viewport_count : wrapper::of_integer<uint32, struct viewport_count_t> {};
	struct scissor_count : wrapper::of_integer<uint32, struct scissor_count_t> {};

	using scissor = vk::rect2d;

	struct pipeline_viewport_state_create_info {
		const uint32 type = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		const void* const next{};
		uint32 flags{};
		vk::viewport_count viewport_count{};
		const vk::viewport* viewports{};
		vk::scissor_count scissor_count{};
		const vk::scissor* scissors{};

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::are_may_contain_decayed_same_as<vk::viewport_count>,
			types::are_may_contain_decayed_same_as<vk::scissor_count>,
			types::are_may_contain_one_range_of_value_type<vk::viewport>,
			types::are_may_contain_one_range_of_value_type<vk::scissor>
		>::for_types<Args...> &&
		(
			(
				!types::are_contain_range_of_value_type<vk::viewport>::for_types<Args...>
				|| !types::are_contain_decayed_same_as<vk::viewport_count>::for_types<Args...>
			) && (
				!types::are_contain_range_of_value_type<vk::scissor>::for_types<Args...>
				|| !types::are_contain_decayed_same_as<vk::scissor_count>::for_types<Args...>
			)
		)
		pipeline_viewport_state_create_info(Args&&... args) {
			if constexpr(types::are_contain_decayed_same_as<vk::viewport_count>::for_types<Args...>) {
				viewport_count = elements::decayed_same_as<vk::viewport_count>(args...);
			}
			if constexpr(types::are_contain_decayed_same_as<vk::scissor_count>::for_types<Args...>) {
				scissor_count = elements::decayed_same_as<vk::scissor_count>(args...);
			}

			if constexpr(types::are_contain_range_of_value_type<vk::viewport>::for_types<Args...>) {
				auto& viewports0 = elements::range_of_value_type<vk::viewport>(args...);
				viewport_count = vk::viewport_count{ (uint32) viewports0.size() };
				viewports = viewports0.data();
			}
			if constexpr(types::are_contain_range_of_value_type<vk::scissor>::for_types<Args...>) {
				auto& scissors0 = elements::range_of_value_type<vk::scissor>(args...);
				scissor_count = vk::scissor_count{ (uint32) scissors0.size() };
				scissors = scissors0.data();
			}
		}

	};

} // vk

static_assert(sizeof(vk::pipeline_viewport_state_create_info) == sizeof(VkPipelineViewportStateCreateInfo));