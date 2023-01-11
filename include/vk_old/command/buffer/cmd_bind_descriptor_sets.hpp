#pragma once

#include "../../descriptor/set/handle.hpp"

namespace vk {

	struct first_set { uint32 _; };
	struct dynamic_offset { uint32 _; };

}

#include "handle.hpp"

#include "../../pipeline/bind_point.hpp"
#include "../../pipeline/layout/handle.hpp"
#include "../../function.hpp"

#include <core/meta/decayed_same_as.hpp>

extern "C" VK_ATTR void VK_CALL vkCmdBindDescriptorSets(
	handle<vk::command_buffer>        command_buffer,
	vk::pipeline_bind_point           pipeline_bind_point,
	handle<vk::pipeline_layout>       layout,
	vk::first_set                     first_set,
	uint32                            descriptor_set_count,
	const handle<vk::descriptor_set>* descriptor_sets,
	uint32                            dynamic_offset_count,
	const vk::dynamic_offset*         dynamic_offsets
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::command_buffer>>,
		types::are_contain_one_decayed<vk::pipeline_bind_point>,
		types::are_contain_one_decayed<handle<vk::pipeline_layout>>,
		types::are_may_contain_one_decayed<vk::first_set>,
		types::are_contain_range_of<handle<vk::descriptor_set>>,
		types::are_may_contain_range_of<vk::dynamic_offset>
	>::for_types<Args...>
	void cmd_bind_descriptor_sets(Args&&... args) {
		auto command_buffer {
			elements::decayed<handle<vk::command_buffer>>(args...)
		};

		vk::pipeline_bind_point bind_point {
			elements::decayed<vk::pipeline_bind_point>(args...)
		};

		auto pipeline_layout {
			elements::decayed<handle<vk::pipeline_layout>>(args...)
		};

		vk::first_set first{};
		
		if constexpr (
			types::are_contain_decayed<vk::first_set>::for_types<Args...>
		) { first = elements::decayed<vk::first_set>(args...); }

		auto& sets = elements::range_of<handle<vk::descriptor_set>>(args...);

		uint32 dynamic_offset_count = 0;
		const vk::dynamic_offset* dynamic_offsets = nullptr;

		if constexpr (
			types::are_contain_range_of<vk::dynamic_offset>::for_types<Args...>
		) {
			auto& offsets = elements::range_of<vk::dynamic_offset>(args...);
			dynamic_offset_count = (uint32) offsets.size();
			dynamic_offsets = offsets.data();
		}

		vkCmdBindDescriptorSets(
			command_buffer,
			bind_point,
			pipeline_layout,
			first,
			(uint32) sets.size(),
			sets.data(),
			dynamic_offset_count,
			dynamic_offsets
		);
	} // cmd_bind_descriptor_sets

} // vk

template<typename... Args>
auto&
handle<vk::command_buffer>::cmd_bind_descriptor_sets(Args &&... args) const {
	vk::cmd_bind_descriptor_sets(*this, forward<Args>(args)...);
	return *this;
}

#include "cmd_bind_descriptor_set.hpp"