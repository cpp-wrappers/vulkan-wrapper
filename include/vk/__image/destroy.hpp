#pragma once

#include "handle.hpp"

#include "../function.hpp"
#include "../destroy_or_free.hpp"
#include "../device_child_destroy_base.hpp"

extern "C" VK_ATTR void VK_CALL vkDestroyImage(
	handle<vk::device> device,
	handle<vk::image>  image,
	const void*        allocator
);

namespace vk {

	template<>
	struct vk::destroy_t<vk::image> :
		vk::device_child_destroy_base<vk::image, vkDestroyImage>
	{};

} // vk