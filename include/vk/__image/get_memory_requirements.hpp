#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/memory_requirements.hpp"
#include "../__device/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct get_image_memory_requirements_function : vk::function<void(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::image>::underlying_type image,
		vk::memory_requirements* memory_requirements
	)> {
		static constexpr auto name = "vkGetImageMemoryRequirements";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::image>>.decayed == 1
	>
	[[nodiscard]] vk::memory_requirements
	get_memory_requirements(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::image> image = a.template
			get<is_same_as<handle<vk::image>>.decayed>();

		vk::memory_requirements memory_requirements;

		vk::get_device_function<vk::get_image_memory_requirements_function>(
			instance, device
		)(
			device.underlying(), image.underlying(), &memory_requirements
		);

		return memory_requirements;

	} // get_image_memory_requirements

} // vk