#pragma once

#include "../../../objects/device/destroy.hpp"
#include "../../../object/destroy_or_free.hpp"
#include "../../../object/device_child_destroy_base.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::command_pool> : vk::device_child_destroy_base<vk::command_pool, VkCommandPool, vkDestroyCommandPool>{};

} // vk