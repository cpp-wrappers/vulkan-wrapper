#pragma once

#include <core/elements/pass_not_satisfying_type_predicate.hpp>
#include "cmd_bind_descriptor_sets.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_contain_one_type<vk::pipeline_bind_point>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::pipeline_layout>,
		types::are_may_contain_one_type<vk::first_set>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::descriptor_set>,
		types::count_of_ranges_of_value_type<vk::dynamic_offset>::less_or_equals<1>
	>::for_types_of<decay<Args>...>
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

}