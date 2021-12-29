#pragma once

#include "create_info.hpp"
#include "handle.hpp"
#include "../../device/handle.hpp"
#include "../../shared/create.hpp"

namespace vk {

	template<>
	struct vk::try_create_t<vk::pipeline_layout> {

		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::vk::contain_one<vk::device>,
				types::count_of_ranges_of_value_type<vk::descriptor_set_layout>::less_or_equals<1>,
				types::count_of_ranges_of_value_type<vk::push_constant_range>::less_or_equals<1>
			>::for_types_of<Args...>
		)
		elements::one_of<vk::result, vk::handle<vk::pipeline_layout>>
		operator () (Args&&... args) const {
			vk::pipeline_layout_create_info ci{};

			if constexpr(types::are_contain_range_of_value_type<vk::descriptor_set_layout>::for_types_of<Args...>) {
				auto& layouts = elements::range_of_value_type<vk::descriptor_set_layout>::for_elements_of(args...);
				ci.descriptor_set_layout_count = (uint32) layouts.size();
				ci.descriptor_set_layouts = layouts.data();
			}

			if constexpr(types::are_contain_range_of_value_type<vk::push_constant_range>::for_types_of<Args...>) {
				auto& push_constant_ranges = elements::range_of_value_type<vk::push_constant_range>::for_elements_of(args...);
				ci.push_constant_range_count = (uint32) push_constant_ranges.size();
				ci.push_constant_ranges = push_constant_ranges.data();
			}

			auto& device = elements::vk::of_type<vk::device>::for_elements_of(args...);

			VkPipelineLayout pipeline_layout;

			vk::result result {
				(int32) vkCreatePipelineLayout(
					(VkDevice) vk::get_handle_value(device),
					(VkPipelineLayoutCreateInfo*) &ci,
					nullptr,
					(VkPipelineLayout*) &pipeline_layout
				)
			};

			if(result.success()) { return vk::handle<vk::pipeline_layout>{ pipeline_layout }; }
			return result;
		}
	};

}