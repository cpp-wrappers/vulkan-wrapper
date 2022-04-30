#pragma once

#include "handle.hpp"

#include "../../function.hpp"
#include "../../device/destroy.hpp"
#include "../../destroy_or_free.hpp"
#include "../../device_child_destroy_base.hpp"

extern "C" VK_ATTR void VK_CALL vkDestroyCommandPool(
	handle<vk::device>       device,
	handle<vk::command_pool> command_pool,
	const void*              allocator
);

namespace vk {

	template<>
	struct vk::destroy_t<vk::command_pool> :
		vk::device_child_destroy_base<
			vk::command_pool, vkDestroyCommandPool
		>
	{};

} // vk