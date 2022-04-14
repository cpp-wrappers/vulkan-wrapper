#pragma once

#include "handle.hpp"

#include "../../function.hpp"

extern "C" VK_ATTR void VK_CALL vkCmdEndRenderPass(
	handle<vk::command_buffer> command_buffer
);

namespace vk {

	void cmd_end_render_pass(handle<vk::command_buffer> command_buffer) {
		vkCmdEndRenderPass(
			command_buffer
		);
	}

} // vk

inline auto& handle<vk::command_buffer>::cmd_end_render_pass() const {
	vk::cmd_end_render_pass(*this);
	return *this;
}