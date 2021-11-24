#pragma once

#include <core/integer.hpp>

#include "../../device/handle.hpp"
#include "../buffer/level.hpp"
#include "../buffer/allocate.hpp"

namespace vk {

	class command_buffer;

	struct command_pool {
		uint64 handle;

		template<type::range_of_value_type<vk::command_buffer> CommandBuffers>
		vk::result try_allocate_command_buffers(
			vk::device device,
			vk::command_buffer_level level,
			CommandBuffers&& command_buffers
		) {
			return vk::try_allocate_command_buffers(device, *this, level, forward<CommandBuffers>(command_buffers));
		}

		template<type::range_of_value_type<vk::command_buffer> CommandBuffers>
		void allocate_command_buffers(
			vk::device device,
			vk::command_buffer_level level,
			CommandBuffers&& command_buffers
		) {
			vk::result result = try_allocate_command_buffers(device, level, forward<CommandBuffers>(command_buffers));
			if(!result.success()) throw result;
		}

	}; // command_pool
} // vk