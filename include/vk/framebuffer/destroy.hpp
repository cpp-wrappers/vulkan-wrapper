#pragma once

#include "handle.hpp"

#include "vk/destroy_or_free.hpp"
#include "vk/device_child_destroy_base.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::framebuffer> : vk::device_child_destroy_base<vk::framebuffer, VkFramebuffer, vkDestroyFramebuffer>{};

} // vk