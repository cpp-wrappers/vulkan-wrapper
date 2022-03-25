#pragma once

#include "../pipeline/stage.hpp"

#include <core/handle/declaration.hpp>

namespace vk {

	struct semaphore;
	struct command_buffer;

	struct submit_info {
		uint32 structure_type = 4;
		const void* next = nullptr;
		uint32 wait_semaphore_count = 0;
		const handle<vk::semaphore>* wait_semaphores = nullptr;
		const vk::pipeline_stages* wait_dst_stage_mask = nullptr;
		uint32 command_buffer_count = 0;
		const handle<vk::command_buffer>* command_buffers = nullptr;
		uint32 signal_semaphore_count = 0;
		const handle<vk::semaphore>* signal_semaphores = nullptr;
	};

} // vk