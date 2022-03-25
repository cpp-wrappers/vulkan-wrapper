#pragma once

#include "handle.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_contain_one_possibly_guarded_handle_of<vk::swapchain>,
		types::are_may_contain_one_possibly_guarded_handle_of<vk::semaphore>,
		types::are_may_contain_one_possibly_guarded_handle_of<vk::fence>,
		types::are_may_contain_one_decayed<vk::timeout>
	>::for_types<Args...>
	vk::expected<vk::image_index>
	try_acquire_next_image(Args&&... args) {
		auto& device = elements::possibly_guarded_handle_of<
			vk::device
		>(args...);

		auto& swapchain = elements::possibly_guarded_handle_of<
			vk::swapchain
		>(args...);
		
		vk::timeout timeout{ UINT64_MAX };

		if constexpr(
			types::are_contain_decayed<vk::timeout>::for_types<Args...>
		) { timeout = elements::decayed<vk::timeout>(args...); }

		handle<vk::semaphore> semaphore{ VK_NULL_HANDLE };

		if constexpr(
			types::are_contain_one_possibly_guarded_handle_of<
				vk::semaphore
			>::for_types<Args...>
		) {
			semaphore = vk::get_handle(
				elements::possibly_guarded_handle_of<vk::semaphore>(args...)
			);
		}

		handle<vk::fence> fence{ VK_NULL_HANDLE };

		if constexpr(
			types::are_contain_one_possibly_guarded_handle_of<
				vk::fence
			>::for_types<Args...>
		) {
			fence = vk::get_handle(
				elements::possibly_guarded_handle_of<vk::fence>(args...)
			);
		}

		uint32 index;

		vk::result result {
			(int32) vkAcquireNextImageKHR(
				(VkDevice) vk::get_handle_value(device),
				(VkSwapchainKHR) vk::get_handle_value(swapchain),
				(uint64) timeout,
				(VkSemaphore) vk::get_handle_value(semaphore),
				(VkFence) vk::get_handle_value(fence),
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