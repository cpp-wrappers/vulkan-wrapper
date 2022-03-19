#pragma once

#include <core/wrapper/of_integer.hpp>

#include "vk/descriptor/set/handle.hpp"

namespace vk {

	struct first_set : wrapper::of_integer<uint32, struct first_set_t> {};
	struct dynamic_offset : wrapper::of_integer<uint32> {};

}

#include "handle.hpp"

#include <core/meta/decayed_same_as.hpp>

#include "vk/pipeline/bind_point.hpp"
#include "vk/pipeline/layout/handle.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_contain_one_decayed<vk::pipeline_bind_point>,
		types::are_contain_one_possibly_guarded_handle_of<vk::pipeline_layout>,
		types::are_may_contain_one_decayed<vk::first_set>,
		types::are_contain_one_range_of<handle<vk::descriptor_set>>,
		types::are_may_contain_one_range_of<vk::dynamic_offset>
	>::for_types<Args...>
	void cmd_bind_descriptor_sets(Args&&... args) {
		auto& command_buffer = elements::possibly_guarded_handle_of<vk::command_buffer>(args...);
		vk::pipeline_bind_point bind_point = elements::decayed<vk::pipeline_bind_point>(args...);
		auto& pipeline_layout = elements::possibly_guarded_handle_of<vk::pipeline_layout>(args...);

		vk::first_set first{};
		
		if constexpr(types::are_contain_decayed<vk::first_set>::for_types<Args...>) {
			first = elements::decayed<vk::first_set>(args...);
		}

		auto& sets = elements::range_of<handle<vk::descriptor_set>>(args...);

		uint32 dynamic_offset_count{};
		const vk::dynamic_offset* dynamic_offsets{};

		if constexpr(types::are_contain_range_of<vk::dynamic_offset>::for_types<Args...>) {
			auto& offsets = elements::range_of<vk::dynamic_offset>(args...);
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

template<typename... Args>
auto& handle<vk::command_buffer>::cmd_bind_descriptor_sets(Args &&... args) const {
	vk::cmd_bind_descriptor_sets(*this, forward<Args>(args)...);
	return *this;
}

#include "cmd_bind_descriptor_set.hpp"