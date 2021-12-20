#pragma once

#include "handle.hpp"
#include "../../device/handle.hpp"

namespace vk {

	struct image_view_guard {
		vk::image_view image_view;
		vk::device device;

		image_view_guard() = default;

		image_view_guard(vk::image_view image_view, vk::device device)
			: image_view{ image_view }, device{ device }
		{}

		template<typename... Args>
		image_view_guard(Args&&... args, vk::device device)
			: image_view{ device.create_image_view(forward<Args>(args)...) }, device{ device }
		{}

		image_view_guard(image_view_guard&& other)
			: image_view{ exchange(other.image_view.handle, 0) }, device{ other.device }
		{}

		image_view_guard& operator = (image_view_guard&& other) {
			image_view.handle = exchange(other.image_view.handle, 0);
			device = other.device;
			return *this;
		}

		~image_view_guard() {
			if(image_view.handle) {
				vkDestroyImageView(
					(VkDevice) device.handle,
					(VkImageView) exchange(image_view.handle, 0),
					(VkAllocationCallbacks*) nullptr
				);
			}
		}

		const vk::image_view& object() const {
			return image_view;
		}

	};
}