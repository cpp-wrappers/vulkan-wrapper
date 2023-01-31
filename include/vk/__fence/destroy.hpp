#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__device/handle.hpp"
#include "../__instance/handle.hpp"

namespace vk {

	struct destroy_fence_function : vk::function<void(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::fence>::underlying_type  fence,
		const void*        allocator
	)> {
		static constexpr auto name = "vkDestroyFence";
	};

	inline void destroy_fence(
		handle<vk::instance> instance,
		handle<vk::device> device,
		handle<vk::fence> fence
	) {
		vk::get_device_function<vk::destroy_fence_function>(
			instance, device
		)(
			device.underlying(), fence.underlying(), nullptr
		);
	}

} // vk