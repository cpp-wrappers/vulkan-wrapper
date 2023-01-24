#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__device/handle.hpp"

namespace vk {

	struct destroy_shader_module_function : vk::function<void(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::shader_module>::underlying_type shader_module,
		const void* allocator
	)> {
		static constexpr auto name = "vkDestroyShaderModule";
	};

	inline void destroy_shader_module(
		handle<vk::instance> instance,
		handle<vk::device> device,
		handle<vk::shader_module> shader_module
	) {
		vk::get_device_function<vk::destroy_shader_module_function>(
			instance, device
		)(
			device.underlying(), shader_module.underlying(), nullptr
		);
	}

} // vk