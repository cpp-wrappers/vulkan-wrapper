#pragma once

#include "cmd_bind_descriptor_sets.hpp"

#include <core/meta/elements/pass_not_satisfying_type_predicate.hpp>

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::command_buffer>>,
		types::are_contain_one_decayed<vk::pipeline_bind_point>,
		types::are_contain_one_decayed<handle<vk::pipeline_layout>>,
		types::are_may_contain_one_decayed<vk::first_set>,
		types::are_contain_one_decayed<handle<vk::descriptor_set>>,
		types::are_may_contain_range_of<vk::dynamic_offset>
	>::for_types<Args...>
	void cmd_bind_descriptor_set(Args&&... args) {
		auto set {
			elements::decayed<handle<vk::descriptor_set>>(args...)
		};

		elements::pass_not_satisfying_type_predicate<
			type::is_decayed<handle<vk::descriptor_set>>
		>(
			forward<Args>(args)...
		)(
			[&]<typename... Args0>(Args0&&... args) {
				vk::cmd_bind_descriptor_sets(
					array{ set },
					forward<Args0>(args)...
				);
			}
		);
	} // cmd_bind_descriptor_set

} // vk

template<typename... Args>
auto&
handle<vk::command_buffer>::cmd_bind_descriptor_set(Args &&... args) const {
	vk::cmd_bind_descriptor_set(*this, forward<Args>(args)...);
	return *this;
}