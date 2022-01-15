#pragma once

#include "../../object/destroy_or_free.hpp"
#include "../../object/device_child_destroy_base.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::buffer> : vk::device_child_destroy_base<vk::buffer, VkBuffer, vkDestroyBuffer>{};

} // vk