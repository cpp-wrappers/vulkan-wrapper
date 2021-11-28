#pragma once

#include <core/integer.hpp>
#include <core/type/range.hpp>
#include "../../shared/result.hpp"
#include "../buffer/level.hpp"

namespace vk {

	class command_buffer;
	class device;

	struct command_pool {
		uint64 handle;

		template<type::range_of_value_type<vk::command_buffer> CommandBuffers>
		vk::result try_allocate_command_buffers(
			vk::device device,
			vk::command_buffer_level level,
			CommandBuffers&& command_buffers
		);

		template<type::range_of_value_type<vk::command_buffer> CommandBuffers>
		void allocate_command_buffers(
			vk::device device,
			vk::command_buffer_level level,
			CommandBuffers&& command_buffers
		);

		template<type::range_of_value_type<vk::command_buffer> CommandBuffers>
		void free_command_buffers(
			vk::device device,
			CommandBuffers&& command_buffers
		);
	}; // command_pool
} // vk

#include "../buffer/allocate.hpp"
#include "../buffer/free.hpp"
#include "../../device/handle.hpp"

template<type::range_of_value_type<vk::command_buffer> CommandBuffers>
vk::result vk::command_pool::try_allocate_command_buffers(
	vk::device device,
	vk::command_buffer_level level,
	CommandBuffers&& command_buffers
) {
	return vk::try_allocate_command_buffers(device, *this, level, forward<CommandBuffers>(command_buffers));
}

template<type::range_of_value_type<vk::command_buffer> CommandBuffers>
void vk::command_pool::allocate_command_buffers(
	vk::device device,
	vk::command_buffer_level level,
	CommandBuffers&& command_buffers
) {
	vk::result result = try_allocate_command_buffers(device, level, forward<CommandBuffers>(command_buffers));
	if(!result.success()) throw result;
}

template<type::range_of_value_type<vk::command_buffer> CommandBuffers>
void vk::command_pool::free_command_buffers(
	vk::device device,
	CommandBuffers&& command_buffers
) {
	vk::free_command_buffers(device, *this, forward<CommandBuffers>(command_buffers));
}