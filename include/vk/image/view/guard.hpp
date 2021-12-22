#pragma once

#include "handle.hpp"
#include "../../device/handle.hpp"
#include "../../shared/guarded.hpp"

namespace vk {

	template<>
	class guarded<vk::image_view> {
		vk::handle<vk::image_view> image_view;
		vk::handle<vk::device> device;

	public:
		guarded() = default;

		guarded(vk::handle<vk::image_view> image_view, vk::handle<vk::device> device)
			: image_view{ image_view }, device{ device }
		{}

		guarded(guarded&& other)
			: image_view{ exchange(other.image_view.value, 0) }, device{ other.device }
		{}

		guarded& operator = (guarded&& other) {
			image_view.value = exchange(other.image_view.value, 0);
			device = other.device;
			return *this;
		}

		~guarded() {
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