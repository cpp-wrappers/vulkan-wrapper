#pragma once

#include "../shared/destroy.hpp"
#include "handle.hpp"
#include "../device/handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::pipeline> {
		void operator() (vk::handle<vk::device> device, vk::handle<vk::pipeline> pipeline) const {
			vkDestroyPipeline(
				(VkDevice) device.value,
				(VkPipeline) pipeline.value,
				nullptr
			);
		}
	};

}