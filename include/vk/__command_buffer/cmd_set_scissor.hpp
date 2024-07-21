#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/rect2d.hpp"
#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"

namespace vk {

	class first_scissor_index {
		uint32 value_;
	public:
		first_scissor_index(uint32 value) : value_ { value } {}
		operator uint32 () const { return value_; }
	};

	struct cmd_set_scissor_function : vk::function<void(*)(
		handle<vk::command_buffer>::underlying_type command_buffer,
		uint32 /*vk::first_scissor_index*/ first_scissor,
		uint32 scissor_count,
		const vk::rect2d* scissors
	)> {
		static constexpr auto name = "vkCmdSetScissor";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::command_buffer>>.decayed == 1,
		is_same_as<vk::first_scissor_index>.decayed <= 1,
		is_range_of_element_type_satisfying_predicate<
			is_same_as<vk::rect2d>.while_decayed
		> == 1
	>
	void cmd_set_scissor(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::command_buffer> command_buffer = a.template
			get_decayed_same_as<handle<vk::command_buffer>>();

		vk::first_scissor_index first{ 0 };
		
		if constexpr (
			(is_same_as<vk::first_scissor_index>.decayed > 0)
			.for_types<Args...>()
		) { first = a.template get_decayed_same_as<vk::first_scissor_index>(); }

		auto& scissors = a.template get_range_of_decayed<vk::rect2d>();

		vk::get_device_function<vk::cmd_set_scissor_function>(
			instance, device
		)(
			command_buffer.underlying(),
			first,
			(uint32) scissors.size(),
			scissors.iterator()
		);
	} // cmd_set_scissor

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::command_buffer>>.decayed == 1,
		is_same_as<vk::first_scissor_index>.decayed <= 1,
		is_same_as<vk::rect2d>.decayed == 1
	>
	void cmd_set_scissor(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::command_buffer> command_buffer = a.template
			get_decayed_same_as<handle<vk::command_buffer>>();

		vk::first_scissor_index first{ 0 };
		
		if constexpr (
			(is_same_as<vk::first_scissor_index>.decayed > 0)
			.for_types<Args...>()
		) { first = a.template get_decayed_same_as<vk::first_scissor_index>(); }

		vk::rect2d scissor = a.template get_decayed_same_as<vk::rect2d>();

		vk::cmd_set_scissor(
			instance, device, command_buffer, first, array{ scissor }
		);
	} // cmd_set_scissor

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::command_buffer>>.decayed == 1,
		is_same_as<vk::first_scissor_index>.decayed <= 1,
		is_same_as<vk::extent<2>>.decayed == 1
	>
	void cmd_set_scissor(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::command_buffer> command_buffer = a.template
			get_decayed_same_as<handle<vk::command_buffer>>();

		vk::first_scissor_index first{ 0 };
		
		if constexpr (
			(is_same_as<vk::first_scissor_index>.decayed > 0)
			.for_types<Args...>()
		) { first = a.template get_decayed_same_as<vk::first_scissor_index>(); }

		vk::extent<2> extent = a.template get_decayed_same_as<vk::extent<2>>();

		vk::cmd_set_scissor(
			instance,
			device,
			command_buffer,
			first,
			vk::rect2d{ .extent{ extent } }
		);
	} // cmd_set_scissor

} // vk