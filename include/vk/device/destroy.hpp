#pragma once

#include "handle.hpp"

#include "../destroy_or_free.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::device> {

		void operator () (handle<vk::device> device) const {
			vkDestroyDevice(
				(VkDevice) vk::get_handle_value(device),
				(VkAllocationCallbacks*) nullptr
			);
		}

	};

} // vk