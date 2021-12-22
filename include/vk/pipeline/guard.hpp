#pragma once

#include "handle.hpp"
#include "../device/handle.hpp"
#include "../shared/guarded.hpp"

namespace vk {

	template<>
	class guarded<vk::pipeline> {
		vk::handle<vk::pipeline> pipeline;
		vk::handle<vk::device> device;

	public:

		guarded() = default;

		guarded(vk::handle<vk::pipeline> pipeline, vk::handle<vk::device> device)
			: pipeline{ pipeline }, device{ device }
		{}

		guarded(guarded&& other)
			: pipeline{ exchange(other.pipeline.value, 0) }, device{ other.device }
		{}

		~guarded() {
			if(pipeline.value) {
				vkDestroyPipeline(
					(VkDevice) device.value,
					(VkPipeline) exchange(pipeline.value, 0),
					nullptr
				);
			}
		}

		const vk::handle<vk::pipeline>& object() const { return pipeline; }
	};
}