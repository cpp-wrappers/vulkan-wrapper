#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include <core/exchange.hpp>
#include <core/elements/one_of.hpp>

#include "../shared/headers.hpp"
#include "../shared/result.hpp"
#include "../device/handle.hpp"

namespace vk {
	elements::one_of<vk::result, vk::handle<vk::semaphore>>
	inline try_create_semaphore(vk::handle<vk::device> device) {
		vk::semaphore_create_info ci{};

		VkSemaphore semaphore;

		vk::result result {
			(int32) vkCreateSemaphore(
				(VkDevice) device.value,
				(VkSemaphoreCreateInfo*) &ci,
				(VkAllocationCallbacks*) nullptr,
				&semaphore
			)
		};

		if(result.success()) return vk::handle<vk::semaphore>{ semaphore };
		return result;
	}

	vk::handle<vk::semaphore> inline create_semaphore(vk::handle<vk::device> device) {
		auto result = try_create_semaphore(device);
		if(result.is_current<vk::result>()) throw result.get<vk::result>();
		return result.get<vk::handle<vk::semaphore>>();
	}
}