#pragma once

#include "./view_images.hpp"

namespace vk {

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::swapchain>>.decayed == 1,
		is_same_as<vk::count>.decayed <= 1,
		is_invokable_with<handle<vk::image>> == 1
	>
	void for_each_images(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::swapchain> swapchain = a.template
			get<is_same_as<handle<vk::swapchain>>.decayed>();


		vk::count count;
		
		if constexpr(
			(is_same_as<vk::count>.decayed > 0).for_types<Args...>()
		) {
			count = (uint32) a.template get<is_same_as<vk::count>.decayed>();
		}
		else {
			count = vk::get_swapchain_image_count(instance, device, swapchain);
		}

		decltype(auto) handler = a.template
			get<is_invokable_with<handle<vk::image>>>();

		vk::view_swapchain_images(
			instance,
			device,
			swapchain,
			count,
			[&](span<handle<vk::image>> image) {
				handler(image);
			}
		);
	}

} // vk

