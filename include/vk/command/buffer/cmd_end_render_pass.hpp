#pragma once

#include "../../shared/guarded_handle.hpp"
#include "handle.hpp"

namespace vk {

	void cmd_end_render_pass(vk::ordinary_or_guarded_handle<vk::command_buffer> auto& command_buffer) {
		vkCmdEndRenderPass(
			(VkCommandBuffer) vk::get_handle_value(command_buffer)
		);
	}
} // vk