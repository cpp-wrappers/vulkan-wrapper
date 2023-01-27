#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"

namespace vk {

	struct destroy_device_function : function<void(*)(
		handle<vk::device>::underlying_type device,
		const void* allocator
	)> {
		static constexpr auto name = "vkDestroyDevice";
	};

	inline void destroy_device(
		handle<vk::instance> instance, handle<vk::device> device
	) {
		get_instance_function<destroy_device_function>(
			instance
		)(
			device.underlying(), nullptr
		);
	}

} // vk