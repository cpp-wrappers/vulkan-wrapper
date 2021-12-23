#pragma once

#include "handle.hpp"
#include "../../device/handle.hpp"
#include "../../shared/guarded_handle.hpp"

namespace vk {

	template<>
	class guarded_handle<vk::image_view> {
		vk::handle<vk::image_view> image_view;
		vk::handle<vk::device> device;

	public:
		guarded_handle() = default;

		guarded_handle(vk::handle<vk::image_view> image_view, vk::handle<vk::device> device)
			: image_view{ image_view }, device{ device }
		{}

		guarded_handle(guarded_handle&& other)
			: image_view{ exchange(other.image_view.value, 0) }, device{ other.device }
		{}

		guarded_handle& operator = (guarded_handle&& other) {
			image_view.value = exchange(other.image_view.value, 0);
			device = other.device;
			return *this;
		}

		~guarded_handle() {
			if(image_view.value) {
				vkDestroyImageView(
					(VkDevice) device.value,
					(VkImageView) exchange(image_view.value, 0),
					(VkAllocationCallbacks*) nullptr
				);
			}
		}

		const vk::handle<vk::image_view>& object() const {
			return image_view;
		}

	};
}