#pragma once

#include "../__internal/function.hpp"
#include "../__device/handle.hpp"
#include "../__buffer/handle.hpp"
#include "../__internal/memory_requirements.hpp"

#include <tuple.hpp>

namespace vk {

	struct get_buffer_memory_requirements_function : vk::function<void(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::buffer>::underlying_type buffer,
		vk::memory_requirements* memory_requirements
	)> {
		static constexpr auto name = "vkGetBufferMemoryRequirements";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::buffer>>.decayed == 1
	>
	vk::memory_requirements
	get_memory_requirements(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::buffer> buffer = a.template
			get<is_same_as<handle<vk::buffer>>.decayed>();

		vk::memory_requirements requirements;

		vk::get_device_function<vk::get_buffer_memory_requirements_function>(
			instance, device
		)(
			device.underlying(),
			buffer.underlying(),
			&requirements
		);

		return requirements;

	} // get_memory_requirements

} // vk