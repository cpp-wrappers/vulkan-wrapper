#pragma once

#include <core/array.hpp>
#include <core/elements/one_of.hpp>
#include <core/range/of_value_type.hpp>
#include <core/wrapper/of.hpp>

#include "../fence/handle.hpp"
#include "../semaphore/handle.hpp"
#include "../command/buffer/handle.hpp"
#include "../shared/result.hpp"
#include "../shared/handle.hpp"
#include "signal_semaphore.hpp"
#include "wait_semaphore.hpp"
#include "submit_info.hpp"
#include "present_info.hpp"

namespace vk {

	struct queue;

	template<>
	struct vk::handle<vk::queue> : vk::handle_base<vk::dispatchable> {

		template<typename... Args>
		void submit(Args&&... args) const;

		vk::result try_present(vk::present_info present_info) const {
			return {
				(int32) vkQueuePresentKHR(
					(VkQueue) value,
					(VkPresentInfoKHR*) &present_info
				)
			};
		}

		inline vk::result try_present(vk::wait_semaphore wait_semaphore, vk::handle<vk::swapchain> swapchain, vk::image_index image_index) const;

		void present(vk::present_info present_info) const {
			vk::result result { try_present(present_info) };
			if(!result.success()) throw result;
		}

		inline void present(vk::wait_semaphore wait_semaphore, vk::handle<vk::swapchain> swapchain, vk::image_index image_index) const;
	};
}

#include "submit.hpp"

template<typename... Args>
void vk::handle<vk::queue>::submit(Args&&... args) const {
	vk::queue_submit(*this, forward<Args>(args)...);
}

#include "../swapchain/handle.hpp"

inline vk::result vk::handle<vk::queue>::try_present(vk::wait_semaphore wait_semaphore, vk::handle<vk::swapchain> swapchain, vk::image_index image_index) const {
	return try_present(vk::present_info {
		.wait_semaphore_count = 1,
		.wait_semaphores = (vk::handle<vk::semaphore>*) &wait_semaphore,
		.swapchain_count = 1,
		.swapchains = &swapchain,
		.image_indices = &image_index
	});
}

void vk::handle<vk::queue>::present(vk::wait_semaphore wait_semaphore, vk::handle<vk::swapchain> swapchain, vk::image_index image_index) const {
	vk::result result { try_present(wait_semaphore, swapchain, image_index) };
	if(!result.success()) throw result;
}