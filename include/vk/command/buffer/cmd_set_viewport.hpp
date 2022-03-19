#pragma once

#include "handle.hpp"

#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

#include "vk/extent.hpp"
#include "vk/viewport.hpp"

namespace vk {

	struct first_viewport_index : wrapper::of_integer<uint32> {};

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_may_contain_one_decayed<vk::first_viewport_index>,
		types::are_contain_one_range_of<vk::viewport>
	>::for_types<Args...>
	void cmd_set_viewport(Args&&... args) {
		auto& command_buffer = elements::possibly_guarded_handle_of<vk::command_buffer>(args...);
		vk::first_viewport_index first{ 0 };
		
		if constexpr(types::are_contain_decayed<vk::first_viewport_index>::for_types<Args...>) {
			first = elements::decayed<vk::first_viewport_index>(args...);
		}

		auto& viewports = elements::range_of<vk::viewport>(args...);

		vkCmdSetViewport(
			(VkCommandBuffer) vk::get_handle_value(command_buffer),
			(uint32) first,
			(uint32) viewports.size(),
			(VkViewport*) viewports.data()
		);
	}

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_may_contain_one_decayed<vk::first_viewport_index>,
		types::are_contain_decayed<vk::viewport>
	>::for_types<Args...>
	void cmd_set_viewport(Args&&... args) {
		auto& command_buffer = elements::possibly_guarded_handle_of<vk::command_buffer>(args...);
		vk::first_viewport_index first{ 0 };
		
		if constexpr(types::are_contain_decayed<vk::first_viewport_index>::for_types<Args...>) {
			first = elements::decayed<vk::first_viewport_index>(args...);
		}

		vk::viewport viewport = elements::decayed<vk::viewport>(args...);

		vk::cmd_set_viewport(command_buffer, first, array{ viewport });
	}

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_may_contain_one_decayed<vk::first_viewport_index>,
		types::are_contain_one_decayed<vk::extent<2>>
	>::for_types<Args...>
	void cmd_set_viewport(Args&&... args) {
		auto& command_buffer = elements::possibly_guarded_handle_of<vk::command_buffer>(args...);
		vk::first_viewport_index first{ 0 };
		
		if constexpr(types::are_contain_decayed<vk::first_viewport_index>::for_types<Args...>) {
			first = elements::decayed<vk::first_viewport_index>(args...);
		}

		vk::extent<2> extent = elements::decayed<vk::extent<2>>(args...);

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
auto& handle<vk::command_buffer>::cmd_set_viewport(Args&&... args) const {
	vk::cmd_set_viewport(*this, forward<Args>(args)...);
	return *this;
}