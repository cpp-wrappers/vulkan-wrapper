#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__device/handle.hpp"

namespace vk {

	struct destroy_image_view_function : vk::function<void(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::image_view>::underlying_type image_view,
		const void* allocator
	)> {
		static constexpr auto name = "vkDestroyImageView";
	};

	template<typename... Args>
	void destroy_pipeline_layout(Args&&... args) {
		handle<vk::instance> instance = tuple{ args... }.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = tuple{ args... }.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::image_view> image_view = tuple{ args... }.template
			get_decayed_same_as<handle<vk::image_view>>();

		vk::get_device_function<vk::destroy_image_view_function>(
			instance, device
		)(
			device.underlying(), image_view.underlying(), nullptr
		);
	}

} // vk