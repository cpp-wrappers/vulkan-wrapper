#pragma once

#include <core/range/of_value_type_same_as.hpp>

#include "vk/handle/base.hpp"
#include "vk/result.hpp"
#include "vk/command/buffer/level.hpp"

namespace vk {

	struct command_buffer;
	struct device;

	struct command_pool;

} // vk

template<>
struct handle<vk::command_pool> : vk::handle_base<vk::non_dispatchable> {

	template<typename... Args>
	void allocate_command_buffers(Args&&...);

	template<range::of<handle<vk::command_buffer>> CommandBuffers>
	void free_command_buffers(
		handle<vk::device> device,
		CommandBuffers&& command_buffers
	);

};

#include "vk/command/buffer/allocate.hpp"
#include "vk/command/buffer/free.hpp"
#include "vk/device/handle.hpp"

template<typename... Args>
void handle<vk::command_pool>::allocate_command_buffers(Args&&... args) {
	vk::allocate_command_buffers(forward<Args>(args)...);
}

template<range::of<handle<vk::command_buffer>> CommandBuffers>
void handle<vk::command_pool>::free_command_buffers(
	handle<vk::device> device,
	CommandBuffers&& command_buffers
) {
	vk::free_command_buffers(device, *this, forward<CommandBuffers>(command_buffers));
}