#pragma once

#include "handle.hpp"

#include "vk/device/destroy.hpp"
#include "vk/destroy_or_free.hpp"
#include "vk/device_child_destroy_base.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::command_pool> : vk::device_child_destroy_base<vk::command_pool, VkCommandPool, vkDestroyCommandPool>{};

} // vk