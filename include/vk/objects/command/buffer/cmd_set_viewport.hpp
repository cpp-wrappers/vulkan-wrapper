#pragma once

#include "handle.hpp"
#include "../../../shared/extent.hpp"
#include "../../../shared/viewport.hpp"

#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

namespace vk {

	struct first_viewport_index : wrapper::of_integer<uint32> {};

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_may_contain_one_decayed_same_as<vk::first_viewport_index>,
		types::are_contain_one_range_of_value_type<vk::viewport>
	>::for_types<Args...>
	void cmd_set_viewport(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>(args...);
		vk::first_viewport_index first{ 0 };
		
		if constexpr(types::are_contain_decayed_same_as<vk::first_viewport_index>::for_types<Args...>) {
			first = elements::decayed_same_as<vk::first_viewport_index>(args...);
		}

		auto& viewports = elements::range_of_value_type<vk::viewport>(args...);

		vkCmdSetViewport(
			(VkCommandBuffer) vk::get_handle_value(command_buffer),
			(uint32) first,
			(uint32) viewports.size(),
			(VkViewport*) viewports.data()
		);
	}

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_may_contain_one_decayed_same_as<vk::first_viewport_index>,
		types::are_contain_decayed_same_as<vk::viewport>
	>::for_types<Args...>
	void cmd_set_viewport(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>(args...);
		vk::first_viewport_index first{ 0 };
		
		if constexpr(types::are_contain_decayed_same_as<vk::first_viewport_index>::for_types<Args...>) {
			first = elements::decayed_same_as<vk::first_viewport_index>(args...);
		}

		vk::viewport viewport = elements::decayed_same_as<vk::viewport>(args...);

		vk::cmd_set_viewport(command_buffer, first, array{ viewport });
	}

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_may_contain_one_decayed_same_as<vk::first_viewport_index>,
		types::are_contain_one_decayed_same_as<vk::extent<2>>
	>::for_types<Args...>
	void cmd_set_viewport(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>(args...);
		vk::first_viewport_index first{ 0 };
		
		if constexpr(types::are_contain_decayed_same_as<vk::first_viewport_index>::for_types<Args...>) {
			first = elements::decayed_same_as<vk::first_viewport_index>(args...);
		}

		vk::extent<2> extent = elements::decayed_same_as<vk::extent<2>>(args...);

		vk::cmd_set_viewport(
			command_buffer,
			first,
			vk::viewport {
				.width = float(extent.width()),
				.height = float(extent.height())
			}
		);
	}

} // vk

template<typename... Args>
auto& vk::handle<vk::command_buffer>::cmd_set_viewport(Args&&... args) const {
	vk::cmd_set_viewport(*this, forward<Args>(args)...);
	return *this;
}