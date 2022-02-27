#pragma once

#include "handle.hpp"

#include "vk/destroy_or_free.hpp"
#include "vk/device_child_destroy_base.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::deferred_operation> :
		vk::device_child_destroy_base<
			vk::deferred_operation,
			VkDeferredOperationKHR,
			vkDestroyDeferredOperationKHR
		>
	{};

} // vk