#pragma once

#include "handle.hpp"
#include "../../device/handle.hpp"
#include "../../shared/guarded_handle.hpp"

namespace vk {

	template<>
	class guarded_handle<vk::pipeline_layout> {
		vk::handle<vk::pipeline_layout> pipeline_layout;
		vk::handle<vk::device> device;

	public:
		guarded_handle() = default;

		guarded_handle(vk::handle<vk::pipeline_layout> pipeline_layout, vk::handle<vk::device> device)
			: pipeline_layout{pipeline_layout}, device{ device }
		{}

		guarded_handle(guarded_handle&& other)
			: pipeline_layout{ exchange(other.pipeline_layout.value, 0) }, device{ other.device }
		{}

		guarded_handle& operator = (guarded_handle&& other) {
			pipeline_layout.value = exchange(other.pipeline_layout.value, 0);
			device = other.device;
			return *this;
		}

		~guarded_handle() {
			if(pipeline_layout.value) {
				vkDestroyPipelineLayout(
					(VkDevice) device.value,
					(VkPipelineLayout) exchange(pipeline_layout.value, 0),
					(VkAllocationCallbacks*) nullptr
				);
			}
		}

		const vk::handle<vk::pipeline_layout>& object() const {
			return pipeline_layout;
		}
	};
}