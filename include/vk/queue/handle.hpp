#pragma once

#include <core/elements/one_of.hpp>
#include <core/range/of_value_type.hpp>
#include <core/array.hpp>
#include <core/wrapper/of.hpp>

#include "submit_info.hpp"
#include "present_info.hpp"
#include "../shared/result.hpp"
#include "../fence/handle.hpp"
#include "../semaphore/handle.hpp"
#include "../command/buffer/handle.hpp"

namespace vk {

	struct wait_semaphore : wrapper::of<vk::semaphore, struct wait_semaphore_t> {};
	struct signal_semaphore : wrapper::of<vk::semaphore, struct signal_semaphore_t> {};

	struct queue {
		void* handle;

		vk::result try_submit(range::of_value_type<vk::submit_info> auto&& submits, vk::fence fence = { VK_NULL_HANDLE }) const {
			return vk::result {
				(int32)vkQueueSubmit(
					(VkQueue) handle,
					(uint32) submits.size(),
					(VkSubmitInfo*) submits.data(),
					(VkFence) fence.handle
				)
			};
		}

		vk::result try_submit(vk::submit_info submit, vk::fence fence = { VK_NULL_HANDLE }) const {
			return try_submit(array{ submit }, fence);
		}

		vk::result try_submit(
			vk::wait_semaphore wait_semaphore,
			vk::pipeline_stages wait_dst_stages,
			vk::command_buffer command_buffer,
			vk::signal_semaphore signal_semaphore,
			vk::fence fence = { VK_NULL_HANDLE }
		) const {
			return try_submit(
				vk::submit_info {
					.wait_semaphore_count = 1,
					.wait_semaphores = (vk::semaphore*) &wait_semaphore,
					.wait_dst_stage_mask = &wait_dst_stages,
					.command_buffer_count = 1,
					.command_buffers = &command_buffer,
					.signal_semaphore_count = 1,
					.signal_semaphores = (vk::semaphore*) &signal_semaphore
				},
				fence
			);
		}

		void submit(vk::submit_info submit, vk::fence fence = { VK_NULL_HANDLE }) const {
			vk::result result = try_submit(submit, fence);
			if(!result.success()) throw result;
		}

		void submit(
			vk::wait_semaphore wait_semaphore,
			vk::pipeline_stages wait_dst_stages,
			vk::command_buffer command_buffer,
			vk::signal_semaphore signal_semaphore,
			vk::fence fence = { VK_NULL_HANDLE }
		) const {
			vk::result result = try_submit(wait_semaphore, wait_dst_stages, command_buffer, signal_semaphore, fence);
			if(!result.success()) throw result;
		}

		vk::result try_present(vk::present_info present_info) const {
			return {
				(int32) vkQueuePresentKHR(
					(VkQueue) handle,
					(VkPresentInfoKHR*) &present_info
				)
			};
		}

		inline vk::result try_present(vk::wait_semaphore wait_semaphore, vk::swapchain swapchain, vk::image_index image_index) const;

		void present(vk::present_info present_info) const {
			vk::result result { try_present(present_info) };
			if(!result.success()) throw result;
		}

		inline void present(vk::wait_semaphore wait_semaphore, vk::swapchain swapchain, vk::image_index image_index) const;
	};
}

#include "../swapchain/handle.hpp"

inline vk::result vk::queue::try_present(vk::wait_semaphore wait_semaphore, vk::swapchain swapchain, vk::image_index image_index) const {
	return try_present(vk::present_info {
		.wait_semaphore_count = 1,
		.wait_semaphores = (vk::semaphore*) &wait_semaphore,
		.swapchain_count = 1,
		.swapchains = &swapchain,
		.image_indices = &image_index
	});
}

void vk::queue::present(vk::wait_semaphore wait_semaphore, vk::swapchain swapchain, vk::image_index image_index) const {
	vk::result result { try_present(wait_semaphore, swapchain, image_index) };
	if(!result.success()) throw result;
}