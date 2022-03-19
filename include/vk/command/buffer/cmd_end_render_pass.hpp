#pragma once

#include "handle.hpp"

#include <core/handle/possibly_guarded_of.hpp>

#include "vk/handle/get_value.hpp"

namespace vk {

	void cmd_end_render_pass(possibly_guarded_handle_of<vk::command_buffer> auto& command_buffer) {
		vkCmdEndRenderPass(
			(VkCommandBuffer) vk::get_handle_value(command_buffer)
		);
	}

} // vk

inline auto& handle<vk::command_buffer>::cmd_end_render_pass() const {
	vk::cmd_end_render_pass(*this);
	return *this;
}