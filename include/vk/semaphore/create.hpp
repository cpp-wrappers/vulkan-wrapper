#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include <core/exchange.hpp>
#include <core/elements/one_of.hpp>

#include "../shared/headers.hpp"
#include "../shared/guarded_handle.hpp"
#include "../shared/result.hpp"
#include "../device/handle.hpp"

namespace vk {
	elements::one_of<vk::result, vk::handle<vk::semaphore>>
	try_create_semaphore(vk::ordinary_or_guarded_handle<vk::device> auto&& device) {
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

	template<vk::ordinary_or_guarded_handle<vk::device> Device>
	vk::handle<vk::semaphore> create_semaphore(Device&& device) {
		auto result = try_create_semaphore(forward<Device>(device));
		if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
		return result.template get<vk::handle<vk::semaphore>>();
	}
}