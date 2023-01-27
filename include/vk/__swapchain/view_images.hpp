#pragma once

#include "./get_images.hpp"
#include "./get_image_count.hpp"

namespace vk {

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::swapchain>> == 1,
		count_of_decayed_same_as<handle<vk::count>> <= 1,
		count_of_invokable_with<span<handle<vk::image>>> == 1
	>
	decltype(auto) view_swapchain_images(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::swapchain> swapchain = a.template
			get_decayed_same_as<handle<vk::swapchain>>();


		vk::count count;
		
		if constexpr(types<Args...>::template
			count_of_decayed_same_as<vk::count> > 0
		) {
			count = (uint32) a.template get_decayed_same_as<vk::count>();
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
			get_invokable_with<span<handle<vk::image>>>();

		return handler(span{ images, (uint32)count });
	}

} // vk

