#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/viewport.hpp"
#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"

namespace vk {

	class first_viewport_index {
		uint32 value_;
	public:
		first_viewport_index(uint32 value) : value_{ value } {}
		operator uint32 () { return value_; }
	};

	struct cmd_set_viewport_function : vk::function<void(*)(
		handle<vk::command_buffer>::underlying_type command_buffer,
		uint32 first_viewport_index,
		uint32 viewport_count,
		const vk::viewport* viewports
	)> {
		static constexpr auto name = "vkCmdSetViewport";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::command_buffer>>.decayed == 1,
		is_same_as<vk::first_viewport_index>.decayed <= 1,
		is_range_of_element_type_satisfying_predicate<
			is_same_as<vk::viewport>.decayed
		> == 1
	>
	void cmd_set_viewport(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::command_buffer> command_buffer = a.template
			get<is_same_as<handle<vk::command_buffer>>.decayed>();

		vk::first_viewport_index first{ 0 };
		
		if constexpr (
			(is_same_as<vk::first_viewport_index>.decayed > 0)
			.for_types<Args...>()
		) {
			first = a.template
				get<is_same_as<vk::first_viewport_index>.decayed>();
		}

		auto& viewports = a.template
			get<is_range_of<is_same_as<vk::viewport>.decayed>>();

		vk::get_device_function<vk::cmd_set_viewport_function>(
			instance, device
		)(
			command_buffer.underlying(),
			first,
			(uint32) viewports.size(),
			viewports.iterator()
		);
	} // cmd_set_viewport

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::command_buffer>>.decayed == 1,
		is_same_as<vk::first_viewport_index>.decayed <= 1,
		is_same_as<vk::viewport>.decayed == 1
	>
	void cmd_set_viewport(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::command_buffer> command_buffer = a.template
			get<is_same_as<handle<vk::command_buffer>>.decayed>();

		vk::first_viewport_index first{ 0 };
		
		if constexpr (
			(is_same_as<vk::first_viewport_index>.decayed > 0)
			.for_types<Args...>()
		) {
			first = a.template
				get<is_same_as<vk::first_viewport_index>.decayed>();
		}

		vk::viewport viewport = a.template
			get<is_same_as<vk::viewport>.decayed>();

		vk::cmd_set_viewport(
			instance, device, command_buffer, first, array{ viewport }
		);
	} // cmd_set_viewport

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::command_buffer>>.decayed == 1,
		is_same_as<vk::first_viewport_index>.decayed <= 1,
		is_same_as<vk::extent<2>>.decayed == 1
	>
	void cmd_set_viewport(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::command_buffer> command_buffer = a.template
			get<is_same_as<handle<vk::command_buffer>>.decayed>();

		vk::first_viewport_index first{ 0 };
		
		if constexpr (
			(is_same_as<vk::first_viewport_index>.decayed > 0)
			.for_types<Args...>()
		) {
			first = a.template
				get<is_same_as<vk::first_viewport_index>.decayed>();
		}

		vk::extent<2> extent = a.template
			get<is_same_as<vk::extent<2>>.decayed>();

		vk::cmd_set_viewport(
			instance,
			device,
			command_buffer,
			first,
			vk::viewport {
				.width = (float) extent.width(),
				.height = (float) extent.height()
			}
		);
	} // cmd_set_viewport

} // vk