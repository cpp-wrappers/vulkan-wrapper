#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include <core/exchange.hpp>
#include <core/elements/one_of.hpp>

#include "../shared/headers.hpp"
#include "../shared/result.hpp"


namespace vk {
	elements::one_of<vk::result, vk::semaphore>
	inline try_create_semaphore(const vk::device& device) {
		vk::semaphore_create_info ci{};

		VkSemaphore semaphore;

		vk::result result {
			(uint32) vkCreateSemaphore(
				*(VkDevice*) &device,
				(VkSemaphoreCreateInfo*) &ci,
				(VkAllocationCallbacks*) nullptr,
				&semaphore
			)
		};

		if(result.success()) return (uint64) semaphore;
		return result;
	}

	vk::semaphore inline create_semaphore(const vk::device& device) {
		return try_create_semaphore(device).move<vk::semaphore>();
	}
}