#pragma once

#include "handle.hpp"

#include "vk/destroy_or_free.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::instance> {

		void operator () (vk::handle<vk::instance> instance) const {
			vkDestroyInstance(
				(VkInstance) vk::get_handle_value(instance),
				(VkAllocationCallbacks*) nullptr
			);
		}

	};

} // vk