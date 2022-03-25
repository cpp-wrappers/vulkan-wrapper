#pragma once

#include "handle.hpp"
#include "destroy.hpp"

#include "../handle/guarded/device_child_base.hpp"


template<>
struct guarded_handle<vk::swapchain> : 
	vk::guarded_device_child_handle_base<vk::swapchain>
{
	using base_type = vk::guarded_device_child_handle_base<vk::swapchain>;
	using base_type::base_type;

	template<typename... Args>
	vk::expected<vk::image_index>
	try_acquire_next_image(Args&&... args) const {
		return handle().try_acquire_next_image(
			device(), forward<Args>(args)...
		);
	}

	template<range::of<::handle<vk::image>> Images>
	vk::count get_images(Images&& images) const {
		return handle().get_images(device(), forward<Images>(images));
	}

	vk::count get_image_count() const {
		return handle().get_image_count(device());
	}

	template<typename F>
	void for_each_image(F&& f) const {
		handle().for_each_image(device(), forward<F>(f));
	}

	template<typename F>
	decltype(auto) view_images(F&& f) const {
		return handle().view_images(device(), forward<F>(f));
	}

}; // guarded_handle<swapchain>