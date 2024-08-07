#pragma once

#include <types.hpp>
#include "../__internal/function.hpp"
#include "../__internal/queue_family_index.hpp"
#include "../__queue/handle.hpp"
#include "../__device/handle.hpp"
#include "../__device/queue_index.hpp"

namespace vk {

	struct get_device_queue_function : vk::function<void(*)(
		handle<vk::device>::underlying_type device,
		vk::queue_family_index queue_family_index,
		vk::queue_index queue_index,
		handle<vk::queue>::underlying_type* queue
	)> {
		static constexpr auto name = "vkGetDeviceQueue";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<vk::queue_family_index>.decayed == 1,
		is_same_as<vk::queue_index>.decayed == 1
	>
	handle<vk::queue>
	get_device_queue(Args&&... args) {
		handle<vk::instance> instance = tuple{ args... }.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = tuple{ args... }.template
			get<is_same_as<handle<vk::device>>.decayed>();

		vk::queue_family_index queue_family_index = tuple{ args... }.template
			get<is_same_as<vk::queue_family_index>.decayed>();

		vk::queue_index queue_index = tuple{ args... }.template
			get<is_same_as<vk::queue_index>.decayed>();

		handle<vk::queue> queue;

		vk::get_device_function<vk::get_device_queue_function>(
			instance, device
		)(
			device.underlying(),
			queue_family_index,
			queue_index,
			&queue.underlying()
		);

		return queue;
	}

} // vk