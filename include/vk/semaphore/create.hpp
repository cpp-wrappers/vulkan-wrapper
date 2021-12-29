#pragma once

#include "../shared/create_or_allocate.hpp"
#include "../device/handle.hpp"
#include "handle.hpp"
#include "create_info.hpp"

namespace vk {

	template<>
	struct vk::try_create_t<vk::semaphore> {

		elements::one_of<vk::result, vk::handle<vk::semaphore>>
		operator () (vk::ordinary_or_guarded_handle<vk::device> auto&& device) const {
			vk::semaphore_create_info ci{};

			VkSemaphore semaphore;

			vk::result result {
				(int32) vkCreateSemaphore(
					(VkDevice) vk::get_handle_value(device),
					(VkSemaphoreCreateInfo*) &ci,
					(VkAllocationCallbacks*) nullptr,
					&semaphore
				)
			};

			if(result.success()) return vk::handle<vk::semaphore>{ semaphore };
			return result;
		}
	};

}