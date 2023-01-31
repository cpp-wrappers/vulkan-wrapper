#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__device/handle.hpp"
#include "../__instance/handle.hpp"

namespace vk {

	struct destroy_semaphore_function : vk::function<void(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::semaphore>::underlying_type semaphore,
		const void* allocator
	)> {
		static constexpr auto name = "vkDestroySemaphore";
	};

	inline void destroy_semaphore(
		handle<vk::instance> instance,
		handle<vk::device> device,
		handle<vk::semaphore> semaphore
	) {
		vk::get_device_function<vk::destroy_semaphore_function>(
			instance, device
		)(
			device.underlying(), semaphore.underlying(), nullptr
		);
	}

} // vk