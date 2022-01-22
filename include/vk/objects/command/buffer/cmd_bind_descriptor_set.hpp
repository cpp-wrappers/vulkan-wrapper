#pragma once

#include "cmd_bind_descriptor_sets.hpp"

#include <core/meta/elements/pass_not_satisfying_type_predicate.hpp>

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_contain_one_decayed_same_as<vk::pipeline_bind_point>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::pipeline_layout>,
		types::are_may_contain_one_decayed_same_as<vk::first_set>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::descriptor_set>,
		types::are_may_contain_one_range_of_value_type<vk::dynamic_offset>
	>::for_types<Args...>
	void cmd_bind_descriptor_set(Args&&... args) {
		auto& set = elements::vk::possibly_guarded_handle_of<vk::descriptor_set>(args...);

		elements::pass_not_satisfying_type_predicate<type::vk::is_possibly_guarded_handle_of<vk::descriptor_set>>(
			forward<Args>(args)...
		)(
			[&]<typename... Args0>(Args0&&... args) {
				vk::cmd_bind_descriptor_sets(array<vk::handle<vk::descriptor_set>, 1>{ vk::get_handle(set) }, forward<Args0>(args)...);
			}
		);
	}

} // vk