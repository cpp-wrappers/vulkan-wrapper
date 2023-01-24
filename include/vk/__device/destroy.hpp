#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"

namespace vk {

	struct destroy_device_function : function<void(*)(
		vk::device** device,
		const void* allocator
	)> {
		static constexpr auto name = "vkDestroyDevice";
	};

	inline void destroy_device(body<vk::device>& device) {
		get_instance_function<destroy_device_function>(
			device.get_instance_handle()
		)(&device->underlying(), nullptr);
	}

} // vk