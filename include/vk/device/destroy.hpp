#pragma once

#include "handle.hpp"

#include "../destroy_or_free.hpp"

extern "C" VK_ATTR void VK_CALL vkDestroyDevice(
	handle<vk::device> device,
	const void*        allocator
);

namespace vk {

	template<>
	struct vk::destroy_t<vk::device> {

		void operator () (handle<vk::device> device) const {
			vkDestroyDevice(
				device,
				nullptr
			);
		}

	};

} // vk