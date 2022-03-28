#pragma once

#include "handle.hpp"

#include "../../device/destroy.hpp"
#include "../../destroy_or_free.hpp"
#include "../../device_child_destroy_base.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::command_pool> :
		vk::device_child_destroy_base<
			vk::command_pool, VkCommandPool, vkDestroyCommandPool
		>
	{};

} // vk