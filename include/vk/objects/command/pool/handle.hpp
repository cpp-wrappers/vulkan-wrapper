#pragma once

#include <core/range/of_value_type.hpp>

#include "../../../object/handle/base.hpp"
#include "../../../shared/result.hpp"
#include "../buffer/level.hpp"

namespace vk {

	struct command_buffer;
	struct device;

	struct command_pool;

	template<>
	struct vk::handle<vk::command_pool> : vk::handle_base<vk::non_dispatchable> {

		template<range::of_value_type<vk::handle<vk::command_buffer>> CommandBuffers>
		[[nodiscard]] vk::result allocate_command_buffers(
			vk::handle<vk::device> device,
			vk::command_buffer_level level,
			CommandBuffers&& command_buffers
		);

		template<range::of_value_type<vk::handle<vk::command_buffer>> CommandBuffers>
		void free_command_buffers(
			vk::handle<vk::device> device,
			CommandBuffers&& command_buffers
		);
	}; // command_pool
} // vk

#include "../buffer/allocate.hpp"
#include "../buffer/free.hpp"
#include "../../device/handle.hpp"

template<range::of_value_type<vk::handle<vk::command_buffer>> CommandBuffers>
vk::result vk::handle<vk::command_pool>::allocate_command_buffers(
	vk::handle<vk::device> device,
	vk::command_buffer_level level,
	CommandBuffers&& command_buffers
) {
	return vk::allocate_command_buffers(device, *this, level, forward<CommandBuffers>(command_buffers));
}

template<range::of_value_type<vk::handle<vk::command_buffer>> CommandBuffers>
void vk::handle<vk::command_pool>::free_command_buffers(
	vk::handle<vk::device> device,
	CommandBuffers&& command_buffers
) {
	vk::free_command_buffers(device, *this, forward<CommandBuffers>(command_buffers));
}