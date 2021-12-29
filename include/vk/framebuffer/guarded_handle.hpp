#pragma once

#include <core/exchange.hpp>

#include "handle.hpp"
#include "../device/handle.hpp"
#include "../shared/headers.hpp"
#include "../shared/guarded_device_child_handle.hpp"

namespace vk {
	
	template<>
	struct guarded_handle<vk::framebuffer> : vk::guarded_device_child_handle_base<vk::framebuffer> {
		using base_type = vk::guarded_device_child_handle_base<vk::framebuffer>;

		using base_type::base_type;

		guarded_handle& operator = (guarded_handle&& other) = default;

		void reset(vk::handle<vk::framebuffer> v) {
			if(handle().value) {
				vkDestroyFramebuffer(
					(VkDevice) device().value,
					(VkFramebuffer) handle().value,
					nullptr
				);
			}
			handle() = v;
		}
	};
}