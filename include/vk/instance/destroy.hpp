#pragma once

#include "../headers.hpp"

namespace vk {

class instance;

inline void destroy_instance(vk::instance& instance) {
	vkDestroyInstance(
		(VkInstance)&instance,
		nullptr
	);
}

}