#pragma once

#include "pipeline.hpp"
#include "device.hpp"

namespace vk {

	class pipeline_guard {
		vk::pipeline pipeline;
		vk::device device;

	public:
		~pipeline_guard() {
			if(pipeline.handle) {
				vkDestroyPipeline(
					(VkDevice) device.handle,
					(VkPipeline) exchange(pipeline.handle, 0),
					nullptr
				);
			}
		}
	};
}