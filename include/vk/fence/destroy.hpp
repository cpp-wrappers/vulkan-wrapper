#pragma once

#include "../shared/destroy.hpp"
#include "handle.hpp"
#include "../device/handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::fence> {
		void operator() (vk::handle<vk::device> device, vk::handle<vk::fence> fence) const {
			vkDestroyFence(
				(VkDevice) device.value,
				(VkFence) fence.value,
				nullptr
			);
		}
	};

}