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
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::device_memory>>.decayed == 1
	>
	void unmap_memory(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::device_memory> device_memory = a.template
			get<is_same_as<handle<vk::device_memory>>.decayed>();

		vk::get_device_function<vk::unmap_memory_function>(
			instance, device
		)(
			device.underlying(),
			device_memory.underlying()
		);
	}

} // vk