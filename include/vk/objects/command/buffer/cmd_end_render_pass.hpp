#pragma once

#include "../../../object/handle/concepts.hpp"
#include "handle.hpp"

namespace vk {

	void cmd_end_render_pass(vk::possibly_guarded_handle_of<vk::command_buffer> auto& command_buffer) {
		vkCmdEndRenderPass(
			(VkCommandBuffer) vk::get_handle_value(command_buffer)
		);
	}

} // vk