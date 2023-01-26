#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__internal/result.hpp"
#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"

namespace vk {

	struct end_command_buffer_function : vk::function<int32(*)(
		handle<vk::command_buffer>::underlying_type command_buffer
	)> {
		static constexpr auto name = "vkEndCommandBuffer";
	};

	inline vk::result try_end_command_buffer(
		handle<vk::instance> instance,
		handle<vk::device> device,
		handle<vk::command_buffer> command_buffer
	) {
		return vk::get_device_function<vk::end_command_buffer_function>(
			instance, device
		)(command_buffer.underlying());
	}

	inline void end_command_buffer(
		handle<vk::instance> instance,
		handle<vk::device> device,
		handle<vk::command_buffer> command_buffer
	) {
		vk::result result = vk::try_end_command_buffer(
			instance,
			device,
			command_buffer
		);
		if(result.error()) vk::unexpected_handler(result);
	}

} // vk