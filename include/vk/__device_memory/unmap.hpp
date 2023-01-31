#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/result.hpp"
#include "../__device/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct unmap_memory_function : vk::function<void(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::device_memory>::underlying_type memory
	)> {
		static constexpr auto name = "vkUnmapMemory";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::device_memory>> == 1
	>
	void unmap_memory(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::device_memory> device_memory = a.template
			get_decayed_same_as<handle<vk::device_memory>>();

		vk::get_device_function<vk::unmap_memory_function>(
			instance, device
		)(
			device.underlying(),
			device_memory.underlying()
		);
	}

} // vk