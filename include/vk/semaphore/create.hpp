#pragma once

#include "handle.hpp"
#include "create_info.hpp"
#include "../create_or_allocate.hpp"
#include "../device/handle.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::semaphore> {

		vk::expected<vk::handle<vk::semaphore>>
		operator () (vk::possibly_guarded_handle_of<vk::device> auto&& device) const {
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
			return vk::handle<vk::semaphore>{ semaphore };
		}

	};

} // vk