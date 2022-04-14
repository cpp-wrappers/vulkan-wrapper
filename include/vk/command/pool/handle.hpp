#pragma once

#include "../../handle/base.hpp"
#include "../../result.hpp"
#include "../../command/buffer/level.hpp"
#include "../../create_or_allocate.hpp"

#include <core/range/of_value_type_same_as.hpp>
#include <core/handle/declaration.hpp>

namespace vk {

	struct command_buffer;
	struct device;

	struct command_pool;

	template<>
	constexpr inline bool is_creatable<vk::command_pool> = true;

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
	vk::allocate_command_buffers(*this, forward<Args>(args)...);
}

template<range::of<handle<vk::command_buffer>> CommandBuffers>
void handle<vk::command_pool>::free_command_buffers(
	handle<vk::device> device,
	CommandBuffers&& command_buffers
) {
	vk::free_command_buffers(device, *this, forward<CommandBuffers>(command_buffers));
}