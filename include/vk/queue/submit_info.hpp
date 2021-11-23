#pragma once

#include <core/integer.hpp>

#include "../shared/headers.hpp"
#include "../pipeline/stage.hpp"

namespace vk {

	class semaphore;
	class command_buffer;

	struct submit_info {
		uint32 type = (uint32) VK_STRUCTURE_TYPE_SUBMIT_INFO;
		const void* next;
		uint32 wait_semaphore_count;
		const vk::semaphore* wait_semaphores;
		const vk::pipeline_stage* wait_dst_stage_mask;
		uint32 command_buffer_count;
		const vk::command_buffer* command_buffers;
		uint32 signal_semaphore_count;
		const vk::semaphore* signal_semaphores;
	};

	
}

static_assert(sizeof(vk::submit_info) == sizeof(VkSubmitInfo));