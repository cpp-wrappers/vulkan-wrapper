#pragma once

#include "handle.hpp"

#include "../../handle/get_value.hpp"
#include "../../function.hpp"

#include <core/handle/possibly_guarded_of.hpp>

extern "C" VK_ATTR void VK_CALL vkCmdEndRenderPass(
	handle<vk::command_buffer> command_buffer
);

namespace vk {

	template<possibly_guarded_handle_of<vk::command_buffer> CommandBuffer>
	void cmd_end_render_pass(CommandBuffer& command_buffer) {
		vkCmdEndRenderPass(
			vk::get_handle(command_buffer)
		);
	}

} // vk

inline auto& handle<vk::command_buffer>::cmd_end_render_pass() const {
	vk::cmd_end_render_pass(*this);
	return *this;
}