#pragma once

#include "handle.hpp"

#include "../function.hpp"
#include "../destroy_or_free.hpp"

extern "C" VK_ATTR void VK_CALL vkDestroyInstance(
	handle<vk::instance> instance,
	const void* allocator
);

namespace vk {

	template<>
	struct vk::destroy_t<vk::instance> {

		void operator () (handle<vk::instance> instance) const {
			vkDestroyInstance(
				instance,
				nullptr
			);
		}

	};

} // vk