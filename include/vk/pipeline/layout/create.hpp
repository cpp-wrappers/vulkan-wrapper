#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/types/are_contain_range_of_value_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/range_of_value_type.hpp>

#include "create_info.hpp"

namespace vk {

	struct device;
	struct pipeline_layout;

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_ranges_of_value_type<vk::descriptor_set_layout>::less_or_equals<1u>,
			types::count_of_ranges_of_value_type<vk::push_constant_range>::less_or_equals<1u>
		>::for_types_of<Args...>
	)
	pipeline_layout& create_pipeline_layout(Args&&... args) {
		vk::pipeline_layout_create_info ci{};

		if constexpr(types::are_contain_range_of_value_type<vk::descriptor_set_layout>::for_types_of<Args...>) {
			auto& layouts = elements::range_of_value_type<vk::descriptor_set_layout>::for_elements_of(args...);
			ci.descriptor_set_layout_count = (primitive::uint32)(primitive::uint) layouts.size();
			ci.descriptor_set_layouts = layouts.data();
		}

		if constexpr(types::are_contain_range_of_value_type<vk::push_constant_range>::for_types_of<Args...>) {
			auto push_constant_ranges = elements::range_of_value_type<vk::push_constant_range>::for_elements_of(args...);
			ci.push_constant_range_count = (primitive::uint32)(primitive::uint) push_constant_ranges.size();
			ci.push_constant_ranges = push_constant_ranges.data();
		}

		vk::pipeline_layout* pipeline_layout;

		vk::throw_if_error(
			vkCreatePipelineLayout(
				(VkDevice) & elements::of_type<vk::device&>::for_elements_of(args...),
				(VkPipelineLayoutCreateInfo*)&ci,
				nullptr,
				(VkPipelineLayout*) &pipeline_layout
			)
		);

		return *pipeline_layout;
	}
}