#pragma once

#include "handle.hpp"
#include "../../device/handle.hpp"

namespace vk {

	struct pipeline_layout_guard {
		vk::pipeline_layout pipeline_layout;
		vk::device device;

		pipeline_layout_guard() = default;

		pipeline_layout_guard(vk::pipeline_layout pipeline_layout, vk::device device)
			: pipeline_layout{pipeline_layout}, device{ device }
		{}

		pipeline_layout_guard(vk::pipeline_layout_guard&& other)
			: pipeline_layout{ exchange(other.pipeline_layout.handle, 0) }, device{ other.device }
		{}

		pipeline_layout_guard& operator = (vk::pipeline_layout_guard&& other) {
			pipeline_layout.handle = exchange(other.pipeline_layout.handle, 0);
			device = other.device;
			return *this;
		}

		~pipeline_layout_guard() {
			if(pipeline_layout.handle) {
				vkDestroyPipelineLayout(
					(VkDevice) device.handle,
					(VkPipelineLayout) exchange(pipeline_layout.handle, 0),
					(VkAllocationCallbacks*) nullptr
				);
			}
		}

		const vk::pipeline_layout& object() const {
			return pipeline_layout;
		}
	};
}