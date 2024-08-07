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
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::image_view>>.decayed == 1
	>
	void destroy_image_view(Args&&... args) {
		handle<vk::instance> instance = tuple{ args... }.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = tuple{ args... }.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::image_view> image_view = tuple{ args... }.template
			get<is_same_as<handle<vk::image_view>>.decayed>();

		vk::get_device_function<vk::destroy_image_view_function>(
			instance, device
		)(
			device.underlying(), image_view.underlying(), nullptr
		);
	}

} // vk