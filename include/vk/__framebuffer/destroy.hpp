#pragma once

#include "../__internal/function.hpp"
#include "../__framebuffer/handle.hpp"
#include "../__device/handle.hpp"
#include "../__instance/handle.hpp"

namespace vk {

	struct destry_framebuffer_function : vk::function<void(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::framebuffer>::underlying_type framebuffer,
		const void* allocator
	)> {
		static constexpr auto name = "vkDestroyFramebuffer";
	};

	inline void destroy_framebuffer(
		handle<vk::instance> instance,
		handle<vk::device> device,
		handle<vk::framebuffer> framebuffer
	) {
		vk::get_device_function<vk::destry_framebuffer_function>(
			instance, device
		)(device.underlying(), framebuffer.underlying(), nullptr);
	}

} // vk