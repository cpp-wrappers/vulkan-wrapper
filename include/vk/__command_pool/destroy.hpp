#pragma once

#include "./handle.hpp"
#include "../__device/handle.hpp"
#include "../__internal/function.hpp"

#include <handle.hpp>

namespace vk {

	struct destroy_command_pool_function : vk::function<void(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::command_pool>::underlying_type command_pool,
		const void* allocator
	)> {
		static constexpr auto name = "vkDestroyCommandPool";
	};

	inline void destroy_command_pool(
		handle<vk::instance> instance,
		handle<vk::device> device,
		handle<vk::command_pool> command_pool
	) {
		vk::get_device_function<destroy_command_pool_function>(
			instance, device
		)(
			device.underlying(), command_pool.underlying(), nullptr
		);
	}

} // vk