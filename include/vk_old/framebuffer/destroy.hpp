#pragma once

#include "handle.hpp"

#include "../function.hpp"
#include "../destroy_or_free.hpp"
#include "../device_child_destroy_base.hpp"

extern "C" VK_ATTR void VK_CALL vkDestroyFramebuffer(
	handle<vk::device>      device,
	handle<vk::framebuffer> framebuffer,
	const void*             allocator
);

namespace vk {

	template<>
	struct vk::destroy_t<vk::framebuffer> :
		vk::device_child_destroy_base<vk::framebuffer, vkDestroyFramebuffer>
	{};

} // vk