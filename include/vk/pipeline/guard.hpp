#pragma once

#include "handle.hpp"
#include "../device/handle.hpp"
#include "../shared/guarded.hpp"

namespace vk {

	template<>
	class guarded<vk::pipeline> {
		vk::pipeline pipeline;
		vk::device device;

	public:

		guarded() = default;

		guarded(vk::pipeline pipeline, vk::device device)
			: pipeline{ pipeline }, device{ device }
		{}

		guarded(guarded&& other)
			: pipeline{ exchange(other.pipeline.handle, 0) }, device{ other.device }
		{}

		~guarded() {
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