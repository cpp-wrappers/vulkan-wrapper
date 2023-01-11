#pragma once

#include "handle.hpp"
#include "../../function.hpp"

#include "../../destroy_or_free.hpp"
#include "../../device_child_destroy_base.hpp"

extern "C" VK_ATTR void VK_CALL vkDestroyBufferView(
	handle<vk::device>      device,
	handle<vk::buffer_view> buffer,
	const void*             allocator
);

namespace vk {

	template<>
	struct vk::destroy_t<vk::buffer_view> :
		vk::device_child_destroy_base<vk::buffer_view, vkDestroyBufferView>
	{};

} // vk