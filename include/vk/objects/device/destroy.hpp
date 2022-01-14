#pragma once

#include "../../object/destroy_or_free.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::device> {

		void operator () (vk::handle<vk::device> device) const {
			vkDestroyDevice(
				(VkDevice) vk::get_handle_value(device),
				(VkAllocationCallbacks*) nullptr
			);
		}

	};
}