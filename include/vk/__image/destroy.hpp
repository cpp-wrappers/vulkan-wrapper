#pragma once

#include "./handle.hpp"
#include "../__device/handle.hpp"
#include "../__instance/handle.hpp"
#include "../__internal/function.hpp"

namespace vk {

	struct destroy_image_function : vk::function<void(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::image>::underlying_type image,
		const void* allocator
	)> {
		static constexpr auto name = "vkDestroyImage";
	};

	inline void destroy_image(
		handle<vk::instance> instance,
		handle<vk::device> device,
		handle<vk::image> image
	) {
		vk::get_device_function<vk::destroy_image_function>(
			instance, device
		)(
			device.underlying(), image.underlying(), nullptr
		);
	}

} // vk