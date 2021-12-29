#pragma once

#include "../shared/destroy.hpp"
#include "handle.hpp"
#include "../instance/handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::surface> {

		void operator () (vk::handle<vk::instance> instance, vk::handle<vk::surface> surface) const {
			vkDestroySurfaceKHR(
				(VkInstance) instance.value,
				(VkSurfaceKHR) surface.value,
				nullptr
			);
		}

	};

}