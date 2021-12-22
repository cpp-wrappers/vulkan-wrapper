#pragma once

#include "handle.hpp"
#include "../shared/guarded.hpp"
#include "../device/handle.hpp"

namespace vk {

	template<>
	class guarded<vk::buffer> {
		vk::buffer buffer;
		vk::device device;

	public:

		guarded() = default;

		guarded(vk::buffer buffer, vk::device device)
			: buffer{ buffer }, device{ device }
		{}

		guarded(guarded&& other)
			: buffer{ exchange(other.buffer.handle, 0) }, device{ other.device }
		{}

		~guarded() {
			if(buffer.handle) {
				vkDestroyBuffer(
					(VkDevice) device.handle,
					(VkBuffer) exchange(buffer.handle, 0),
					(VkAllocationCallbacks*) nullptr
				);
			}
		}
	};

}