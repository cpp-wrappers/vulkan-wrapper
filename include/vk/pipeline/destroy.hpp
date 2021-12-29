#pragma once

#include "../device/handle.hpp"
#include "../shared/destroy_or_free.hpp"
#include "handle.hpp"

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