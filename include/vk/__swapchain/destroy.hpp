#pragma once

#include "../__internal/function.hpp"
#include "../__device/handle.hpp"
#include "../__instance/handle.hpp"
#include "../__swapchain/handle.hpp"

namespace vk {

	struct destroy_swapchain_function : vk::function<void(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::swapchain>::underlying_type swapchain,
		const void* allocator
	)> {
		static constexpr auto name = "vkDestroySwapchainKHR";
	};

	inline void destroy_swapchain(
		handle<vk::instance> instance,
		handle<vk::device> device,
		handle<vk::swapchain> swapchain
	) {
		vk::get_device_function<vk::destroy_swapchain_function>(
			instance, device
		)(
			device.underlying(), swapchain.underlying(), nullptr
		);
	}

} // vk