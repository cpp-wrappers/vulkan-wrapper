#pragma once

#include "handle.hpp"
#include "../../device/handle.hpp"
#include "../../shared/guarded.hpp"

namespace vk {

	template<>
	class guarded<vk::image_view> {
		vk::image_view image_view;
		vk::device device;

	public:
		guarded() = default;

		guarded(vk::image_view image_view, vk::device device)
			: image_view{ image_view }, device{ device }
		{}

		template<typename... Args>
		guarded(Args&&... args, vk::device device)
			: image_view{ device.create_image_view(forward<Args>(args)...) }, device{ device }
		{}

		guarded(guarded&& other)
			: image_view{ exchange(other.image_view.handle, 0) }, device{ other.device }
		{}

		guarded& operator = (guarded&& other) {
			image_view.handle = exchange(other.image_view.handle, 0);
			device = other.device;
			return *this;
		}

		~guarded() {
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