#pragma once

#include "handle.hpp"
#include "../device/handle.hpp"

namespace vk {

	class pipeline_guard {
		vk::pipeline pipeline;
		vk::device device;

	public:

		pipeline_guard() = default;

		pipeline_guard(vk::pipeline pipeline, vk::device device)
			: pipeline{ pipeline }, device{ device }
		{}

		pipeline_guard(pipeline_guard&& other)
			: pipeline{ exchange(other.pipeline.handle, 0) }, device{ other.device }
		{}

		~pipeline_guard() {
			if(pipeline.handle) {
				vkDestroyPipeline(
					(VkDevice) device.handle,
					(VkPipeline) exchange(pipeline.handle, 0),
					nullptr
				);
			}
		}

		const vk::pipeline& object() const { return pipeline; }
	};
}