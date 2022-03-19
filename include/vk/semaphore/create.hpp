#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include "vk/create_or_allocate.hpp"
#include "vk/device/handle.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::semaphore> {

		vk::expected<handle<vk::semaphore>>
		operator () (possibly_guarded_handle_of<vk::device> auto&& device) const {
			vk::semaphore_create_info ci{};

			VkSemaphore semaphore;

			vk::result result {
				(int32) vkCreateSemaphore(
					(VkDevice) vk::get_handle_value(device),
					(VkSemaphoreCreateInfo*) &ci,
					(VkAllocationCallbacks*) nullptr,
					(VkSemaphore*) &semaphore
				)
			};

			if(result.error()) return result;
			return handle<vk::semaphore>{ semaphore };
		}

	};

} // vk