#pragma once

#include "handle.hpp"
#include "../../device/handle.hpp"
#include "../../shared/guarded.hpp"

namespace vk {

	template<>
	class guarded<vk::pipeline_layout> {
		vk::pipeline_layout pipeline_layout;
		vk::device device;

	public:
		guarded() = default;

		guarded(vk::pipeline_layout pipeline_layout, vk::device device)
			: pipeline_layout{pipeline_layout}, device{ device }
		{}

		guarded(guarded&& other)
			: pipeline_layout{ exchange(other.pipeline_layout.handle, 0) }, device{ other.device }
		{}

		guarded& operator = (guarded&& other) {
			pipeline_layout.handle = exchange(other.pipeline_layout.handle, 0);
			device = other.device;
			return *this;
		}

		~guarded() {
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