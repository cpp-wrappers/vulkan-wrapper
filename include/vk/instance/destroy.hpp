#pragma once

#include "../shared/headers.hpp"

namespace vk::internal {
	struct instance;

	inline void destroy_instance(vk::internal::instance* instance) {
		vkDestroyInstance(
			(VkInstance) instance,
			nullptr
		);
	}

}