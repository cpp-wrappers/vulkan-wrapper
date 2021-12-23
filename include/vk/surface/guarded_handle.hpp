#pragma once

#include <core/exchange.hpp>

#include "handle.hpp"
#include "../instance/handle.hpp"
#include "../shared/guarded_instance_child_handle.hpp"

namespace vk {
	struct instance;

	template<>
	struct vk::guarded_handle<vk::surface> : vk::guarded_instance_child_handle_base<vk::surface> {
		using base_type = vk::guarded_instance_child_handle_base<vk::surface>;

		using base_type::base_type;

		guarded_handle& operator = (guarded_handle&&) = default;

		~guarded_handle() {
			if(handle().value) {
				vkDestroySurfaceKHR(
					(VkInstance) instance().value,
					(VkSurfaceKHR) exchange(handle().value, 0),
					nullptr
				);
			}
		}
	};
}