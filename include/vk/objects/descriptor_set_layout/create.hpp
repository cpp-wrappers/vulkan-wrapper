#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/types/are_contain_range_of_value_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/for_each_of_type.hpp>
#include <core/elements/range_of_value_type.hpp>

#include "create_info.hpp"
#include "../result.hpp"

namespace vk {
	struct device;
	struct descriptor_set_layout;

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::device&>::equals<1u>,
			types::count_of_type<vk::descriptor_set_layout_create_flag>::remove_reference::greater_or_equals<0u>,
			types::count_of_ranges_of_value_type<vk::descriptor_set_layout_binding>::less_or_equals<1u>
		>::for_types_of<Args...>
	)
	descriptor_set_layout& create_descriptor_set_layout(Args&&... args) {
		vk::descriptor_set_layout_create_info ci {};

		elements::for_each_of_type_remove_reference<vk::descriptor_set_layout_create_flag>(
			[&](auto f) { ci.flags.set(f); },
			args...
		);

		if constexpr(types::are_contain_range_of_value_type<vk::descriptor_set_layout_binding>::for_types_of<Args...>) {
			auto& bindings = elements::range_of_value_type<vk::descriptor_set_layout_binding&>::for_elements_of(args...);
			ci.binding_count = (primitive::uint32)(primitive::uint) bindings.size();
			ci.bindings = bindings.data();
		}

		vk::descriptor_set_layout* descriptor_set_layout;

		vk::throw_if_error(
			vkCreateDescriptorSetLayout(
				(VkDevice) elements::of_type<vk::device&>::for_elements_of(args...),
				(VkDescriptorSetLayoutCreateInfo*) &ci,
				nullptr,
				(VkDescriptorSetLayout*) &descriptor_set_layout
			)
		);

		return *descriptor_set_layout;
	}
}