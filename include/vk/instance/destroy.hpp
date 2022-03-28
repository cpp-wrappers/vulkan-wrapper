#pragma once

#include "handle.hpp"

#include "../destroy_or_free.hpp"

extern "C" void vkDestroyInstance(
	VkInstance,
	const VkAllocationCallbacks*
);

namespace vk {

	template<>
	struct vk::destroy_t<vk::instance> {

		void operator () (handle<vk::instance> instance) const {
			vkDestroyInstance(
				(VkInstance) vk::get_handle_value(instance),
				(VkAllocationCallbacks*) nullptr
			);
		}

	};

} // vk