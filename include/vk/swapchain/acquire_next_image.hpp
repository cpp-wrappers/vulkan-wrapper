#pragma once

#include "handle.hpp"

#include "../function.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

extern "C" VK_ATTR int32 VK_CALL vkAcquireNextImageKHR(
	handle<vk::device> device,
	handle<vk::swapchain> swapchain,
	uint64 timeout,
	handle<vk::semaphore> semaphore,
	handle<vk::fence> fence,
	uint32* image_index
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::device>>,
		types::are_contain_one_decayed<handle<vk::swapchain>>,
		types::are_may_contain_one_decayed<handle<vk::semaphore>>,
		types::are_may_contain_one_decayed<handle<vk::fence>>,
		types::are_may_contain_one_decayed<vk::timeout>
	>::for_types<Args...>
	vk::expected<vk::image_index>
	try_acquire_next_image(Args&&... args) {
		auto device {
			elements::decayed<handle<vk::device>>(args...)
		};

		auto swapchain {
			elements::decayed<handle<vk::swapchain>>(args...)
		};
		
		vk::timeout timeout{ ~uint64{ 0 } };

		if constexpr (
			types::are_contain_decayed<vk::timeout>::for_types<Args...>
		) { timeout = elements::decayed<vk::timeout>(args...); }

		handle<vk::semaphore> semaphore{};

		if constexpr (
			types::are_contain_decayed<
				handle<vk::semaphore>
			>::for_types<Args...>
		) { semaphore = elements::decayed<handle<vk::semaphore>>(args...); }

		handle<vk::fence> fence{};

		if constexpr (
			types::are_contain_decayed<
				handle<vk::fence>
			>::for_types<Args...>
		) { fence = elements::decayed<handle<vk::fence>>(args...); }

		uint32 index;

		vk::result result {
			vkAcquireNextImageKHR(
				device,
				swapchain,
				(uint64) timeout,
				semaphore,
				fence,
				&index
			)
		};

		if(result.error()) return result;

		return vk::image_index{ index };
	}

} // vk

template<typename... Args>
vk::expected<vk::image_index>
handle<vk::swapchain>::try_acquire_next_image(Args&&... args) const {
	return vk::try_acquire_next_image(*this, forward<Args>(args)...);
}