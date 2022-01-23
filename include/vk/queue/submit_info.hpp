#pragma once

#include "../headers.hpp"
#include "../handle/declaration.hpp"
#include "../pipeline/stage.hpp"

namespace vk {

	struct semaphore;
	struct command_buffer;

	struct submit_info {
		const uint32 type = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		const void* const next;
		uint32 wait_semaphore_count;
		const vk::handle<vk::semaphore>* wait_semaphores;
		const vk::pipeline_stages* wait_dst_stage_mask;
		uint32 command_buffer_count;
		const vk::handle<vk::command_buffer>* command_buffers;
		uint32 signal_semaphore_count;
		const vk::handle<vk::semaphore>* signal_semaphores;
	};

} // vk

static_assert(sizeof(vk::submit_info) == sizeof(VkSubmitInfo));