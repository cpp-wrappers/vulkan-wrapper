#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__device/handle.hpp"

namespace vk {

	struct destroy_buffer_view_function : vk::function<void(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::buffer_view>::underlying_type buffer_view,
		const void* allocator
	)> {
		static constexpr auto name = "vkDestroyBufferView";
	};

	inline void destroy_buffer_view(
		handle<vk::instance> instance,
		handle<vk::device> device,
		handle<vk::buffer_view> buffer_view
	) {
		vk::get_device_function<vk::destroy_buffer_view_function>(
			instance, device
		)(
			device.underlying(), buffer_view.underlying(), nullptr
		);
	}

} // vk