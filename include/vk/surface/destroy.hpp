#pragma once

#include "../instance/handle.hpp"
#include "../shared/destroy_or_free.hpp"
#include "handle.hpp"

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