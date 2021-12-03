#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include <core/exchange.hpp>
#include <core/elements/one_of.hpp>

#include "../shared/headers.hpp"
#include "../shared/result.hpp"
#include "../device/handle.hpp"

namespace vk {
	elements::one_of<vk::result, vk::semaphore>
	inline try_create_semaphore(const vk::device& device) {
		vk::semaphore_create_info ci{};

		VkSemaphore semaphore;

		vk::result result {
			(int32) vkCreateSemaphore(
				(VkDevice) device.handle,
				(VkSemaphoreCreateInfo*) &ci,
				(VkAllocationCallbacks*) nullptr,
				&semaphore
			)
		};

		if(result.success()) return vk::semaphore{ semaphore };
		return result;
	}

	vk::semaphore inline create_semaphore(const vk::device& device) {
		return try_create_semaphore(device).get<vk::semaphore>();
	}
}