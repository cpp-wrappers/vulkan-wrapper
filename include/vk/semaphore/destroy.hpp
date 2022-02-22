#pragma once

#include "handle.hpp"

#include "vk/destroy_or_free.hpp"
#include "vk/device_child_destroy_base.hpp"
#include "vk/device/handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::semaphore> : vk::device_child_destroy_base<vk::semaphore, VkSemaphore, vkDestroySemaphore>{};

} // vk