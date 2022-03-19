#pragma once

#include <core/handle/declaration.hpp>

#include "vk/headers.hpp"
#include "vk/pipeline/stage.hpp"

namespace vk {

	struct semaphore;
	struct command_buffer;

	struct submit_info {
		const uint32 type = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		const void* const next;
		uint32 wait_semaphore_count;
		const handle<vk::semaphore>* wait_semaphores;
		const vk::pipeline_stages* wait_dst_stage_mask;
		uint32 command_buffer_count;
		const handle<vk::command_buffer>* command_buffers;
		uint32 signal_semaphore_count;
		const handle<vk::semaphore>* signal_semaphores;
	};

} // vk

static_assert(sizeof(vk::submit_info) == sizeof(VkSubmitInfo));