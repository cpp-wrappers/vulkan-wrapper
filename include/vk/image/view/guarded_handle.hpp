#pragma once

#include "handle.hpp"
#include "../../device/handle.hpp"
#include "../../shared/guarded_device_child_handle.hpp"

namespace vk {

	template<>
	struct guarded_handle<vk::image_view> : vk::guarded_device_child_handle_base<vk::image_view> {
		using base_type = vk::guarded_device_child_handle_base<vk::image_view>;

		using base_type::base_type;
		guarded_handle& operator = (guarded_handle&&) = default;

		void reset(vk::handle<vk::image_view> v) {
			if(handle().value) {
				vkDestroyImageView(
					(VkDevice) device().value,
					(VkImageView) handle().value,
					(VkAllocationCallbacks*) nullptr
				);
			}
			handle() = v;
		}
	};
}