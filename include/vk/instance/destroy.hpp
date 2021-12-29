#pragma once

#include "../shared/destroy.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::instance> {

		void operator () (vk::handle<vk::instance> instance) const {
			vkDestroyInstance(
				(VkInstance) instance.value,
				nullptr
			);
		}

	};
}