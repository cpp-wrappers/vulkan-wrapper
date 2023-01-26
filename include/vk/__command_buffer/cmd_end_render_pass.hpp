#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"

namespace vk {

	struct cmd_end_render_pass_function : vk::function<void(*)(
		handle<vk::command_buffer>::underlying_type command_buffer
	)> {
		static constexpr auto name = "vkCmdEndRenderPass";
	};

	inline void cmd_end_render_pass(
		handle<vk::instance> instance,
		handle<vk::device> device,
		handle<vk::command_buffer> command_buffer
	) {
		vk::get_device_function<vk::cmd_end_render_pass_function>(
			instance, device
		)(
			command_buffer.underlying()
		);
	}

} // vk