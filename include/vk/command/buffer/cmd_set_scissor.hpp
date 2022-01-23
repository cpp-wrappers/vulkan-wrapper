#pragma once

#include "handle.hpp"
#include "../../rect2d.hpp"

#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

namespace vk {

	struct first_scissor_index : wrapper::of_integer<uint32> {};

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_may_contain_one_decayed_same_as<vk::first_scissor_index>,
		types::are_contain_one_range_of_value_type<vk::rect2d>
	>::for_types<Args...>
	void cmd_set_scissor(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>(args...);
		vk::first_scissor_index first{ 0 };
		
		if constexpr(types::are_contain_decayed_same_as<vk::first_scissor_index>::for_types<Args...>) {
			first = elements::decayed_same_as<vk::first_scissor_index>(args...);
		}

		auto& scissors = elements::range_of_value_type<vk::rect2d>(args...);

		vkCmdSetScissor(
			(VkCommandBuffer) vk::get_handle_value(command_buffer),
			(uint32) first,
			(uint32) scissors.size(),
			(VkRect2D*) scissors.data()
		);
	}

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_may_contain_one_decayed_same_as<vk::first_scissor_index>,
		types::are_contain_one_decayed_same_as<vk::rect2d>
	>::for_types<Args...>
	void cmd_set_scissor(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>(args...);
		vk::first_scissor_index first{ 0 };
		
		if constexpr(types::are_contain_decayed_same_as<vk::first_scissor_index>::for_types<Args...>) {
			first = elements::decayed_same_as<vk::first_scissor_index>(args...);
		}

		vk::rect2d scissor = elements::decayed_same_as<vk::rect2d>(args...);

		vk::cmd_set_scissor(command_buffer, first, array{ scissor });
	}

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_may_contain_one_decayed_same_as<vk::first_scissor_index>,
		types::are_contain_one_decayed_same_as<vk::extent<2>>
	>::for_types<Args...>
	void cmd_set_scissor(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>(args...);
		vk::first_scissor_index first{ 0 };
		
		if constexpr(types::are_contain_decayed_same_as<vk::first_scissor_index>::for_types<Args...>) {
			first = elements::decayed_same_as<vk::first_scissor_index>(args...);
		}

		vk::extent<2> extent  = elements::decayed_same_as<vk::extent<2>>(args...);

		vk::cmd_set_scissor(command_buffer, first, vk::rect2d{ .extent{ extent } } );
	}

} // vk

template<typename... Args>
auto& vk::handle<vk::command_buffer>::cmd_set_scissor(Args&&... args) const {
	vk::cmd_set_scissor(*this, forward<Args>(args)...);
	return *this;
}