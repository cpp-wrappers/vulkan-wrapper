#pragma once

#include "handle.hpp"

#include "../function.hpp"
#include "../destroy_or_free.hpp"
#include "../device_child_destroy_base.hpp"
#include "../device/handle.hpp"

extern "C" VK_ATTR void VK_CALL vkDestroyRenderPass(
	handle<vk::device>      device,
	handle<vk::render_pass> render_pass,
	const void*             allocator
);

namespace vk {

	template<>
	struct vk::destroy_t<vk::render_pass> :
		vk::device_child_destroy_base<
			vk::render_pass, vkDestroyRenderPass
		>
	{};

} // vk