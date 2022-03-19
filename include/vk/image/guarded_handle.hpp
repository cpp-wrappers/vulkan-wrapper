#pragma once

#include "get_memory_requirements.hpp"
#include "destroy.hpp"

#include "vk/handle/guarded/device_child_base.hpp"

template<>
struct guarded_handle<vk::image> : vk::guarded_device_child_handle_base<vk::image> {
	using base_type = vk::guarded_device_child_handle_base<vk::image>;

	using base_type::base_type;

	template<typename... Args> vk::result try_bind_memory(Args&&...) const;
	template<typename... Args> void bind_memory(Args&&...) const;

	vk::memory_requirements get_memory_requirements() const {
		return vk::get_image_memory_requirements(device(), handle());
	}
};

#include "bind_memory.hpp"

template<typename... Args>
vk::result guarded_handle<vk::image>::try_bind_memory(Args&&... args) const {
	return vk::try_bind_image_memory(device(), handle(), forward<Args>(args)...);
}

template<typename... Args>
void guarded_handle<vk::image>::bind_memory(Args&&... args) const {
	vk::bind_image_memory(device(), handle(), forward<Args>(args)...);
}