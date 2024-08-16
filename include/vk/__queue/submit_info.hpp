#pragma once

#include "../__semaphore/handle.hpp"
#include "../__command_buffer/handle.hpp"
#include "../__pipeline/stage.hpp"

namespace vk {

	struct submit_info {
		const uint32 structure_type = 4;
		const void* next = nullptr;

		uint32 wait_semaphore_count = 0;
		const handle<vk::semaphore>::underlying_type*
			wait_semaphores = nullptr;

		const vk::pipeline_stages* wait_dst_stage_mask = nullptr;
		uint32 command_buffer_count = 0;
		const handle<vk::command_buffer>::underlying_type*
			command_buffers = nullptr;

		uint32 signal_semaphore_count = 0;
		const handle<vk::semaphore>::underlying_type*
			signal_semaphores = nullptr;
	};

} // vk