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
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::command_buffer>> == 1,
		count_of_decayed_same_as<vk::first_viewport_index> <= 1,
		count_of_range_of_decayed<vk::viewport> == 1
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

		auto& viewports = a.template get_range_of_decayed<vk::viewport>();

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
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::command_buffer>> == 1,
		count_of_decayed_same_as<vk::first_viewport_index> <= 1,
		count_of_decayed_same_as<vk::viewport> == 1
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

		vk::viewport viewport = a.template get_decayed_same_as<vk::viewport>();

		vk::cmd_set_viewport(
			instance, device, command_buffer, first, array{ viewport }
		);
	} // cmd_set_viewport

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
			vk::viewport {
				.width = (float) extent.width(),
				.height = (float) extent.height()
			}
		);
	} // cmd_set_viewport

} // vk