#pragma once

#include "handle.hpp"
#include "destroy.hpp"
#include "../shared/guarded_device_child_handle.hpp"

namespace vk {

	template<>
	struct guarded_handle<vk::swapchain> : vk::guarded_device_child_handle_base<vk::swapchain> {
		using base_type = vk::guarded_device_child_handle_base<vk::swapchain>;

		using base_type::base_type;

		guarded_handle(guarded_handle&&) = default;
		guarded_handle& operator = (guarded_handle&&) = default;

		elements::one_of<vk::result, vk::image_index>
		try_acquire_next_image(
			vk::timeout timeout,
			vk::handle<vk::semaphore> semaphore = { VK_NULL_HANDLE },
			vk::handle<vk::fence> fence = {VK_NULL_HANDLE}
		) const {
			return handle().try_acquire_next_image(device(), timeout, semaphore, fence);
		}

		template<range::of_value_type<vk::handle<vk::image>> Images>
		vk::count get_images(Images&& images) const {
			return handle().get_images(device(), forward<Images>(images));
		}

		vk::count get_image_count() const {
			return handle().get_image_count(device());
		}

		template<typename F>
		vk::count for_each_image(F&& f) const {
			return handle().for_each_image(device(), forward<F>(f));
		}
	};
}