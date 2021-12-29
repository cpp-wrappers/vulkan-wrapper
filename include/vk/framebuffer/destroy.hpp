#pragma once

#include "../shared/destroy_or_free.hpp"
#include "handle.hpp"
#include "../device/handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::framebuffer> {
		void operator() (vk::handle<vk::device> device, vk::handle<vk::framebuffer> framebuffer) const {
			vkDestroyFramebuffer(
				(VkDevice) device.value,
				(VkFramebuffer) framebuffer.value,
				nullptr
			);
		}
	};

}