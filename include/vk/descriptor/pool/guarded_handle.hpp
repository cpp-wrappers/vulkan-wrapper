#pragma once

#include "destroy.hpp"

#include "vk/handle/guarded/device_child_base.hpp"
#include "vk/descriptor/set/handle.hpp"

template<>
struct guarded_handle<vk::descriptor_pool> : vk::guarded_device_child_handle_base<vk::descriptor_pool> {
	using base_type = vk::guarded_device_child_handle_base<vk::descriptor_pool>;

	using base_type::base_type;

	template<typename... Args>
	::handle<vk::descriptor_set> allocate_descriptor_set(Args&&...);
};

#include "vk/descriptor/set/allocate.hpp"

template<typename... Args>
handle<vk::descriptor_set> guarded_handle<vk::descriptor_pool>::allocate_descriptor_set(Args&&... args) {
	return vk::allocate<vk::descriptor_set>(device(), handle(), forward<Args>(args)...);
}