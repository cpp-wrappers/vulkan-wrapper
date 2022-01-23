#pragma once

#include "handle.hpp"
#include "../../../object/destroy_or_free.hpp"
#include "../../../object/device_child_destroy_base.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::buffer_view> : vk::device_child_destroy_base<vk::buffer_view, VkBufferView, vkDestroyBufferView> {};

} // vk