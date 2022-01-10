#pragma once

#include "../../../object/destroy_or_free.hpp"
#include "../../device/handle.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::image_view> {

		void operator () (vk::handle<vk::device> device, vk::handle<vk::image_view> image_view) const {
			vkDestroyImageView(
				(VkDevice) device.value,
				(VkImageView) image_view.value,
				nullptr
			);
		}

	};

}