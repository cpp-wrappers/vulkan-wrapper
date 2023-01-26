#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/rect2d.hpp"
#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"

namespace vk {

	struct first_viewport_index { uint32 _; };

	struct cmd_set_viewport_function : vk::function<void(*)(
		handle<vk::command_buffer>::underlying_type command_buffer,
		vk::first_viewport_index first_viewport,
		uint32 viewport_count,
		const vk::rect2d* viewports
	)> {
		static constexpr auto name = "vkCmdSetViewport";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::command_buffer>> == 1,
		count_of_decayed_same_as<vk::first_viewport_index> <= 1,
		count_of_range_of_decayed<vk::rect2d> == 1
	>
	void cmd_set_viewport(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::command_buffer> command_buffer = a.template
			get_decayed_same_as<handle<vk::command_buffer>>();

		vk::first_viewport_index first{ 0 };
		
		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::first_viewport_index> > 0
		) { first = a.template get_decayed_same_as<vk::first_viewport_index>(); }

		auto& scissors = a.template get_range_of_decayed<vk::rect2d>();

		vk::get_device_function<vk::cmd_set_viewport_function>(
			instance, device
		)(
			command_buffer.underlying(),
			first,
			(uint32) scissors.size(),
			scissors.data()
		);
	} // cmd_set_scissor

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::command_buffer>> == 1,
		count_of_decayed_same_as<vk::first_viewport_index> <= 1,
		count_of_decayed_same_as<vk::rect2d> == 1
	>
	void cmd_set_viewport(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::command_buffer> command_buffer = a.template
			get_decayed_same_as<handle<vk::command_buffer>>();

		vk::first_viewport_index first{ 0 };
		
		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::first_viewport_index> > 0
		) { first = a.template get_decayed_same_as<vk::first_viewport_index>(); }

		vk::rect2d scissor = a.template get_decayed_same_as<vk::rect2d>();

		vk::cmd_set_viewport(
			instance, device, command_buffer, first, array{ scissor }
		);
	} // cmd_set_scissor

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::command_buffer>> == 1,
		count_of_decayed_same_as<vk::first_viewport_index> <= 1,
		count_of_decayed_same_as<vk::extent<2>> == 1
	>
	void cmd_set_viewport(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::command_buffer> command_buffer = a.template
			get_decayed_same_as<handle<vk::command_buffer>>();

		vk::first_viewport_index first{ 0 };
		
		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::first_viewport_index> > 0
		) {
			first = a.template get_decayed_same_as<vk::first_viewport_index>();
		}

		vk::extent<2> extent = a.template get_decayed_same_as<vk::extent<2>>();

		vk::cmd_set_viewport(
			instance,
			device,
			command_buffer,
			first,
			vk::rect2d{ .extent{ extent } }
		);
	} // cmd_set_scissor

} // vk