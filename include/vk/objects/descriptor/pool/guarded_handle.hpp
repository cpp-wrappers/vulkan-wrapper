#pragma once

#include "../../../object/handle/guarded/device_child_base.hpp"
#include "../set/handle.hpp"
#include "destroy.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::descriptor_pool> : vk::guarded_device_child_handle_base<vk::descriptor_pool> {
		using base_type = vk::guarded_device_child_handle_base<vk::descriptor_pool>;

		using base_type::base_type;

		template<typename... Args>
		vk::handle<vk::descriptor_set> allocate_descriptor_set(Args&&...);
	};

} // vk

#include "../set/allocate.hpp"

template<typename... Args>
vk::handle<vk::descriptor_set> vk::guarded_handle<vk::descriptor_pool>::allocate_descriptor_set(Args&&... args) {
	return vk::allocate<vk::descriptor_set>(device(), handle(), forward<Args>(args)...);
}