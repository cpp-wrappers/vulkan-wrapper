#pragma once

#include "handle.hpp"
#include "../device/handle.hpp"
#include "../shared/guarded_handle.hpp"

namespace vk {

	template<>
	class guarded_handle<vk::pipeline> {
		vk::handle<vk::pipeline> pipeline;
		vk::handle<vk::device> device;

	public:

		guarded_handle() = default;

		guarded_handle(vk::handle<vk::pipeline> pipeline, vk::handle<vk::device> device)
			: pipeline{ pipeline }, device{ device }
		{}

		guarded_handle(guarded_handle&& other)
			: pipeline{ exchange(other.pipeline.value, 0) }, device{ other.device }
		{}

		~guarded_handle() {
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