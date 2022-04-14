#pragma once

#include "../../function.hpp"
#include "../../destroy_or_free.hpp"
#include "../../device/handle.hpp"

extern "C" VK_ATTR void VK_CALL vkDestroyPipelineLayout(
	handle<vk::device> device,
	handle<vk::pipeline_layout> pipeline_layout,
	const void* allocator
);

namespace vk {

	template<>
	struct vk::destroy_t<vk::pipeline_layout> {

		template<typename... Args>
		void operator () (Args&&... args) const {
			auto device = elements::decayed<handle<vk::device>>(args...);
			auto layout {
				elements::decayed<handle<vk::pipeline_layout>>(args...)
			};

			vkDestroyPipelineLayout(device, layout, nullptr);
		}

	};

} // vk