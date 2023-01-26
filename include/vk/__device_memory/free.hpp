#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__device/handle.hpp"
#include "../__instance/handle.hpp"

namespace vk {

	struct free_memory_function : vk::function<void(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::device_memory>::underlying_type memory,
		const void* allocator
	)> {
		static constexpr auto name = "vkFreeMemory";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::device_memory>> == 1
	>
	void free_memory(Args&&... args) {
		handle<vk::instance> instance = tuple{ args... }.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = tuple{ args... }.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::device_memory> device_memory = tuple{ args... }.template
			get_decayed_same_as<handle<vk::device_memory>>();

		vk::get_device_function<vk::free_memory_function>(
			instance, device
		)(
			device.underlying(), device_memory.underlying(), nullptr
		);
	}

} // vk