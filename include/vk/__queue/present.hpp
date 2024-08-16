#pragma once

#include "./handle.hpp"
#include "./present_info.hpp"
#include "./wait_semaphore.hpp"
#include "../__internal/function.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct queue_present_function : vk::function<int32(*)(
		handle<vk::queue>::underlying_type queue,
		const vk::present_info* present_info
	)> {
		static constexpr auto name = "vkQueuePresentKHR";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::queue>>.decayed == 1,
		is_same_as<vk::present_info>.decayed == 1
	>
	vk::result try_queue_present(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::queue> queue = a.template
			get<is_same_as<handle<vk::queue>>.decayed>();

		vk::present_info present_info = a.template
			get<is_same_as<vk::present_info>.decayed>();

		return {
			vk::get_device_function<vk::queue_present_function>(
				instance, device
			)(
				queue.underlying(),
				&present_info
			)
		};
	}

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::queue>>.decayed == 1,
		is_range_of<is_same_as<vk::wait_semaphore>.decayed> == 1,
		is_range_of<is_same_as<handle<vk::swapchain>>.decayed> == 1,
		is_range_of<is_same_as<vk::image_index>.decayed> == 1,
		is_range_of<is_same_as<vk::result>.decayed> <= 1
	>
	vk::result try_queue_present(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::queue> queue = a.template
			get<is_same_as<handle<vk::queue>>.decayed>();

		auto& wait_semaphores = a.template
			get<is_range_of<is_same_as<vk::wait_semaphore>.decayed>>();
		auto& swapchains = a.template
			get<is_range_of<is_same_as<handle<vk::swapchain>>.decayed>>();
		auto& image_indices = a.template
			get<is_range_of<is_same_as<vk::image_index>.decayed>>();

		vk::present_info present_info {
			.wait_semaphore_count = (uint32) wait_semaphores.size(),
			.wait_semaphores = (const handle<vk::semaphore>::underlying_type*)
				wait_semaphores.iterator(),
			.swapchain_count = (uint32) swapchains.size(),
			.swapchains = (const handle<vk::swapchain>::underlying_type*)
				swapchains.iterator(),
			.image_indices = image_indices.iterator()
		};

		if constexpr (types<Args...>::template
			count_of<is_range_of<is_same_as<vk::result>.decayed>> > 0
		) {
			present_info.results = a.template
				get<is_range_of<is_same_as<vk::result>.decayed>>();
		}
	
		return vk::try_queue_present(instance, device, queue, present_info);
	}

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::queue>>.decayed == 1,
		is_same_as<vk::wait_semaphore>.decayed == 1,
		is_same_as<handle<vk::swapchain>>.decayed == 1,
		is_same_as<vk::image_index>.decayed == 1
	>
	[[nodiscard]] vk::result try_queue_present(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::queue> queue = a.template
			get<is_same_as<handle<vk::queue>>.decayed>();

		handle<vk::semaphore> wait_semaphore =
			(handle<vk::semaphore>)
			a.template get<is_same_as<vk::wait_semaphore>.decayed>();
		
		handle<vk::swapchain> swapchain = a.template
			get<is_same_as<handle<vk::swapchain>>.decayed>();
		vk::image_index image_index = a.template
			get<is_same_as<vk::image_index>.decayed>();

		vk::present_info present_info {
			.wait_semaphore_count = 1,
			.wait_semaphores = &wait_semaphore.underlying(),
			.swapchain_count = 1,
			.swapchains = &swapchain.underlying(),
			.image_indices = &image_index
		};

		return vk::try_queue_present(instance, device, queue, present_info);
	}

	template<typename... Args>
	void queue_present(Args&&... args) {
		vk::result result = vk::try_queue_present(forward<Args>(args)...);
		if (result.error()) {
			vk::unexpected_handler(result);
		}
	}

} // vk