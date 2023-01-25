#pragma once

#include "../__internal/function.hpp"
#include "../__device/handle.hpp"
#include "../__buffer/handle.hpp"
#include "../__instance/handle.hpp"

extern "C" VK_ATTR void VK_CALL vkDestroyBuffer(
	handle<vk::device> device,
	handle<vk::buffer> buffer,
	const void*        allocator
);

namespace vk {

	struct destroy_buffer_function : vk::function<void(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::buffer>::underlying_type buffer,
		const void* allocator
	)> {
		static constexpr auto name = "vkDestroyBuffer";
	};

	inline void destroy_buffer(
		handle<vk::instance> instance,
		handle<vk::device> device,
		handle<vk::buffer> buffer
	) {
		vk::get_device_function<vk::destroy_buffer_function>(
			instance, device
		)(
			device.underlying(), buffer.underlying(), nullptr
		);
	}

} // vk