#pragma once

#include "handle.hpp"
#include "../../handle/get_value.hpp"

namespace vk {

	vk::result try_end_command_buffer(vk::possibly_guarded_handle_of<vk::command_buffer> auto& command_buffer) {
		return {
			(int32) vkEndCommandBuffer((VkCommandBuffer) vk::get_handle_value(command_buffer))
		};
	}

	void end_command_buffer(vk::possibly_guarded_handle_of<vk::command_buffer> auto& command_buffer) {
		vk::result result = vk::try_end_command_buffer(command_buffer);
		if(result.error()) default_unexpected_handler(result);
	}

} // vk

inline vk::result vk::handle<vk::command_buffer>::try_end() const {
	return vk::try_end_command_buffer(*this);
}

inline void vk::handle<vk::command_buffer>::end() const {
	vk::end_command_buffer(*this);
}