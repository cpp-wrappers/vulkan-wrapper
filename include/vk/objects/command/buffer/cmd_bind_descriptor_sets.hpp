#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/are_may_contain_one_type.hpp>

#include "../../pipeline/layout/handle.hpp"
#include "../../descriptor/set/handle.hpp"
#include "handle.hpp"

namespace vk {

	struct first_set : wrapper::of_integer<uint32, struct first_set_t> {};
	struct dynamic_offset : wrapper::of_integer<uint32> {};

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_contain_one_type<vk::pipeline_bind_point>::decay,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::pipeline_layout>,
		types::are_may_contain_one_type<vk::first_set>::decay,
		types::count_of_ranges_of_value_type<vk::handle<vk::descriptor_set>>::equals<1>,
		types::count_of_ranges_of_value_type<vk::dynamic_offset>::less_or_equals<1>
	>::for_types_of<Args...>
	void cmd_bind_descriptor_sets(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>::for_elements_of(args...);
		vk::pipeline_bind_point bind_point = elements::of_type<vk::pipeline_bind_point>::decay::for_elements_of(args...);
		auto& pipeline_layout = elements::vk::possibly_guarded_handle_of<vk::pipeline_layout>::for_elements_of(args...);

		vk::first_set first{};
		
		if constexpr(types::are_contain_type<vk::first_set>::decay::for_types_of<Args...>)
			first = elements::of_type<vk::first_set>::decay::for_elements_of(args...);

		auto& sets = elements::range_of_value_type<vk::handle<vk::descriptor_set>>::for_elements_of(args...);

		uint32 dynamic_offset_count{};
		const vk::dynamic_offset* dynamic_offsets{};

		if constexpr(types::are_contain_range_of_value_type<vk::dynamic_offset>::for_types_of<Args...>) {
			auto& offsets = elements::range_of_value_type<vk::dynamic_offset>::for_elements_of(args...);
			dynamic_offset_count = (uint32) offsets.size();
			dynamic_offsets = offsets.data();
		}

		vkCmdBindDescriptorSets(
			(VkCommandBuffer) vk::get_handle_value(command_buffer),
			(VkPipelineBindPoint) bind_point,
			(VkPipelineLayout) vk::get_handle_value(pipeline_layout),
			(uint32) first,
			(uint32) sets.size(),
			(VkDescriptorSet*) sets.data(),
			(uint32) dynamic_offset_count,
			(uint32*) dynamic_offsets
		);
	}

} // vk