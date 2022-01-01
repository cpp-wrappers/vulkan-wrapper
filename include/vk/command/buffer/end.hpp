#pragma once

#include "handle.hpp"

namespace vk {

	vk::result try_end_command_buffer(vk::ordinary_or_guarded_handle<vk::command_buffer> auto& command_buffer) {
		return {
			(int32) vkEndCommandBuffer((VkCommandBuffer) vk::get_handle_value(command_buffer))
		};
	}

	void end_command_buffer(vk::ordinary_or_guarded_handle<vk::command_buffer> auto& command_buffer) {
		vk::result result = vk::try_end_command_buffer(command_buffer);
		if(!result.success()) throw result;
	}

}