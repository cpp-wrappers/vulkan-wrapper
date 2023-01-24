#pragma once

#include "./handle.hpp"
#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"
#include "../__internal/function.hpp"

namespace vk {

	struct destroy_render_pass_function : vk::function<void(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::render_pass>::underlying_type render_pass,
		const void* allocator
	)> {
		static constexpr auto name = "vkDestroyRenderPass";
	};

	inline void destroy_render_pass(
		handle<vk::instance> instance,
		handle<vk::device> device,
		handle<vk::render_pass> render_pass
	) {
		vk::get_device_function<vk::destroy_render_pass_function>(
			instance, device
		)(
			device.underlying(),
			render_pass.underlying(),
			nullptr
		);
	}

} // vk