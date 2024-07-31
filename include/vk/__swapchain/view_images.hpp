#pragma once

#include "./get_images.hpp"
#include "./get_image_count.hpp"

namespace vk {

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::swapchain>>.decayed == 1,
		is_same_as<vk::count>.decayed <= 1,
		count_of<is_invokable_with<span<handle<vk::image>>>> == 1
	>
	decltype(auto) view_swapchain_images(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::swapchain> swapchain = a.template
			get<is_same_as<handle<vk::swapchain>>.decayed>();


		vk::count count;
		
		if constexpr(
			(is_same_as<vk::count>.decayed > 0)
			.for_types<Args...>()
		) {
			count = (uint32) a.template get<is_same_as<vk::count>.decayed>();
		}
		else {
			count = vk::get_swapchain_image_count(instance, device, swapchain);
		}

		handle<vk::image> images[(uint32)count];

		count = vk::get_swapchain_images(
			instance,
			device,
			swapchain,
			span{ images, (uint32)count }
		);

		decltype(auto) handler = a.template
			get<is_invokable_with<span<handle<vk::image>>>>();

		return handler(span{ images, (uint32)count });
	}

} // vk

