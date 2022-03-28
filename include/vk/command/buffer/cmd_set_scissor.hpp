#pragma once

#include "handle.hpp"
#include "../../rect2d.hpp"
#include "../../function.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

extern "C" VK_ATTR void VK_CALL vkCmdSetScissor(
	handle<vk::command_buffer> command_buffer,
	uint32 first_scissor,
	uint32 scissor_count,
	const vk::rect2d* scissors
);

namespace vk {

	struct first_scissor_index : wrapper::of_integer<uint32> {};

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_may_contain_one_decayed<vk::first_scissor_index>,
		types::are_contain_range_of<vk::rect2d>
	>::for_types<Args...>
	void cmd_set_scissor(Args&&... args) {
		auto& command_buffer = elements::possibly_guarded_handle_of<
			vk::command_buffer
		>(args...);

		vk::first_scissor_index first{ 0 };
		
		if constexpr(
			types::are_contain_decayed<
				vk::first_scissor_index
			>::for_types<Args...>
		) {
			first = elements::decayed<vk::first_scissor_index>(args...);
		}

		auto& scissors = elements::range_of<vk::rect2d>(args...);

		vkCmdSetScissor(
			vk::get_handle(command_buffer),
			(uint32) first,
			(uint32) scissors.size(),
			scissors.data()
		);
	}

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_may_contain_one_decayed<vk::first_scissor_index>,
		types::are_contain_one_decayed<vk::rect2d>
	>::for_types<Args...>
	void cmd_set_scissor(Args&&... args) {
		auto& command_buffer = elements::possibly_guarded_handle_of<
			vk::command_buffer
		>(args...);

		vk::first_scissor_index first{ 0 };
		
		if constexpr(
			types::are_contain_decayed<
				vk::first_scissor_index
			>::for_types<Args...>
		) {
			first = elements::decayed<vk::first_scissor_index>(args...);
		}

		vk::rect2d scissor = elements::decayed<vk::rect2d>(args...);

		vk::cmd_set_scissor(command_buffer, first, array{ scissor });
	}

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_may_contain_one_decayed<vk::first_scissor_index>,
		types::are_contain_one_decayed<vk::extent<2>>
	>::for_types<Args...>
	void cmd_set_scissor(Args&&... args) {
		auto& command_buffer = elements::possibly_guarded_handle_of<
			vk::command_buffer
		>(args...);

		vk::first_scissor_index first{ 0 };
		
		if constexpr(
			types::are_contain_decayed<
				vk::first_scissor_index
			>::for_types<Args...>
		) {
			first = elements::decayed<vk::first_scissor_index>(args...);
		}

		vk::extent<2> extent  = elements::decayed<vk::extent<2>>(args...);

		vk::cmd_set_scissor(
			command_buffer,
			first,
			vk::rect2d{ .extent{ extent } }
		);
	}

} // vk

template<typename... Args>
auto& handle<vk::command_buffer>::cmd_set_scissor(Args&&... args) const {
	vk::cmd_set_scissor(*this, forward<Args>(args)...);
	return *this;
}