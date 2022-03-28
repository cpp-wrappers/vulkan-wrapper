#pragma once

#include "handle.hpp"
#include "../../handle/get_value.hpp"
#include "../../result.hpp"
#include "../../function.hpp"

#include <core/handle/possibly_guarded_of.hpp>

extern "C" VK_ATTR int32 VK_CALL vkEndCommandBuffer(
	handle<vk::command_buffer> command_buffer
);

namespace vk {

	template<possibly_guarded_handle_of<vk::command_buffer> CommandBuffer>
	vk::result try_end_command_buffer(CommandBuffer& command_buffer) {
		return {
			vkEndCommandBuffer(vk::get_handle(command_buffer))
		};
	}

	template<possibly_guarded_handle_of<vk::command_buffer> CommandBuffer>
	void end_command_buffer(CommandBuffer& command_buffer) {
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