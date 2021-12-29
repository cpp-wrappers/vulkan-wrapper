#pragma once

#include "../../shared/destroy_or_free.hpp"
#include "../../device/handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::pipeline_layout> {

		void operator () (vk::handle<vk::device> device, vk::handle<vk::pipeline_layout> pipeline_layout) const {
			vkDestroyPipelineLayout(
				(VkDevice) device.value,
				(VkPipelineLayout) pipeline_layout.value,
				(VkAllocationCallbacks*) nullptr
			);
		}

	};

}