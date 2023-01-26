#pragma once

#include "./render_pass_begin_info.hpp"
#include "../__internal/function.hpp"
#include "../__command_buffer/handle.hpp"
#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct cmd_begin_render_pass_function : vk::function<void(*)(
		handle<vk::command_buffer>::underlying_type command_buffer,
		const vk::render_pass_begin_info* render_pass_begin,
		int32 contents
	)> {
		static constexpr auto name = "vkCmdBeginRenderPass";
	};
	
	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::command_buffer>> == 1,
		count_of_decayed_same_as<vk::render_pass_begin_info> == 1
	>
	void cmd_begin_render_pass(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::command_buffer> command_buffer = a.template
			get_decayed_same_as<handle<vk::command_buffer>>();

		auto& render_pass_begin_info = a.template
			get_decayed_same_as<vk::render_pass_begin_info>();

		vk::get_device_function<vk::cmd_begin_render_pass_function>(
			instance, device
		)(
			command_buffer.underlying(),
			&render_pass_begin_info,
			0
		);
	} // cmd_begin_render_pass

	template<nuint Order, typename... Args>
	void cmd_begin_render_pass(Args&&... args) {
		static_assert(Order > 0);
		cmd_begin_render_pass<Order - 1>(forward<Args>(args)...);
	}

	template<nuint Order, typename... Args>
	requires
	(Order == 0) &&
	types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::command_buffer>> == 1,
		count_of_decayed_same_as<handle<vk::render_pass>> == 1,
		count_of_decayed_same_as<handle<vk::framebuffer>> == 1,
		count_of_decayed_same_as<vk::render_area> == 1,
		count_of_range_of_decayed<vk::clear_value> == 1
	>
	void cmd_begin_render_pass(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::command_buffer> command_buffer = a.template
			get_decayed_same_as<handle<vk::command_buffer>>();

		handle<vk::render_pass> render_pass = a.template
			get_decayed_same_as<handle<vk::render_pass>>();

		handle<vk::framebuffer> framebuffer = a.template
			get_decayed_same_as<handle<vk::framebuffer>>();

		auto& clear_values = a.template
			get_range_of_decayed<vk::clear_value>();

		vk::render_area render_area = a.template
			get_decayed_same_as<vk::render_area>();

		return vk::cmd_begin_render_pass(
			instance,
			device,
			command_buffer,
			vk::render_pass_begin_info {
				.render_pass = render_pass.underlying(),
				.framebuffer = framebuffer.underlying(),
				.render_area = render_area,
				.clear_value_count = (uint32) clear_values.size(),
				.clear_values = clear_values.iterator()
			}
		);
	} // cmd_begin_render_pass

	template<nuint Order, typename... Args>
	requires
	(Order == 1) &&
	(types<Args...>::template count_of_decayed_same_as<vk::clear_value> == 1)
	void cmd_begin_render_pass(Args&&... args) {
		vk::clear_value clear_value = tuple{ args... }.template
			get_decayed_same_as<vk::clear_value>();

		tuple{ args... }.template
		pass_satisfying_predicate<
			!is_same_as<vk::clear_value>.while_decayed
		>([]<typename... Args0>(Args0&&... args0) {
			cmd_begin_render_pass<Order - 1>(
				::array{ clear_value },
				::forward<Args0>(args0)...
			);
		});
	}

	template<typename... Args>
	void cmd_begin_render_pass(Args&&... args) {
		cmd_begin_render_pass<2>(forward<Args>(args)...);
	}

} // vk