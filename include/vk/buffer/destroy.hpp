#pragma once

#include "../shared/destroy_or_free.hpp"
#include "handle.hpp"
#include "../device/handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::buffer> {

		void operator () (vk::handle<vk::device> device, vk::handle<vk::buffer> buffer) const {
			vkDestroyBuffer(
				(VkDevice) device.value,
				(VkBuffer) buffer.value,
				nullptr
			);
		}

	};

}