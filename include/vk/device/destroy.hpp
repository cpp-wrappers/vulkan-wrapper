#pragma once

#include "handle.hpp"

#include "vk/destroy_or_free.hpp"

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

} // vk