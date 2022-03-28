#pragma once

#include "handle.hpp"

#include "../../function.hpp"
#include "../../destroy_or_free.hpp"
#include "../../device_child_destroy_base.hpp"
#include "../../device/handle.hpp"

extern "C" VK_ATTR void VK_CALL vkDestroyDescriptorPool(
	handle<vk::device> device,
	handle<vk::descriptor_pool> descriptor_pool,
	const void* allocator
);

namespace vk {

	template<>
	struct vk::destroy_t<vk::descriptor_pool> :
		vk::device_child_destroy_base<
			vk::descriptor_pool, vkDestroyDescriptorPool
		>
	{};

} // vk