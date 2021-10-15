#pragma once

#include "../headers.hpp"

namespace vk {

	struct device;

	void inline destroy_device(vk::device& device) {
		vkDestroyDevice(
			(VkDevice) &device,
			nullptr
		);
	}

}