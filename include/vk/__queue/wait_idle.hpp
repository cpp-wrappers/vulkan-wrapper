#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/result.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"

namespace vk {

	struct queue_wait_idle_function : vk::function<int32(*)(
		handle<vk::queue>::underlying_type queue
	)> {
		static constexpr auto name = "vkQueueWaitIdle";
	};

	inline vk::result try_queue_wait_idle(
		handle<vk::instance> instance,
		handle<vk::device> device,
		handle<vk::queue> queue
	) {
		return {
			vk::get_device_function<vk::queue_wait_idle_function>(
				instance, device
			)(
				queue.underlying()
			)
		};
	}

	template<typename... Args>
	void queue_wait_idle(Args&&... args) {
		vk::result result = vk::try_queue_wait_idle(forward<Args>(args)...);
		if (result.error()) {
			vk::unexpected_handler(result);
		}
	}

}