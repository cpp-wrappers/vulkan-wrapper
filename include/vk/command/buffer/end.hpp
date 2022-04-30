#pragma once

#include "handle.hpp"
#include "../../result.hpp"
#include "../../function.hpp"

extern "C" VK_ATTR int32 VK_CALL vkEndCommandBuffer(
	handle<vk::command_buffer> command_buffer
);

namespace vk {

	inline vk::result try_end_command_buffer(
		handle<vk::command_buffer> command_buffer
	) {
		return {
			vkEndCommandBuffer(command_buffer)
		};
	}

	inline void end_command_buffer(
		handle<vk::command_buffer> command_buffer
	) {
		vk::result result = vk::try_end_command_buffer(command_buffer);
		if(result.error()) vk::unexpected_handler(result);
	}

} // vk

inline vk::result handle<vk::command_buffer>::try_end() const {
	return vk::try_end_command_buffer(*this);
}

inline void handle<vk::command_buffer>::end() const {
	vk::end_command_buffer(*this);
}