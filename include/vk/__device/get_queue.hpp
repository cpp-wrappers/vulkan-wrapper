#pragma once

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
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<vk::queue_family_index> == 1,
		count_of_decayed_same_as<vk::queue_index> == 1
	>
	handle<vk::queue>
	get_device_queue(Args&&... args) {
		handle<vk::instance> instance = tuple{ args... }.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = tuple{ args... }.template
			get_decayed_same_as<handle<vk::device>>();

		vk::queue_family_index queue_family_index = tuple{ args... }.template
			get_decayed_same_as<vk::queue_family_index>();

		vk::queue_index queue_index = tuple{ args... }.template
			get_decayed_same_as<vk::queue_index>();

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