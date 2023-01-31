#pragma once

#include "./handle.hpp"
#include "./memory_properties.hpp"
#include "../__internal/function.hpp"
#include "../__instance/handle.hpp"

namespace vk {

	struct get_physical_device_memory_properties_function :
		vk::function<void(*)(
			handle<vk::physical_device>::underlying_type physical_device,
			vk::physical_device_memory_properties* memory_properties
		)>
	{
		static constexpr auto name = "vkGetPhysicalDeviceMemoryProperties";
	};

	[[ nodiscard ]]
	vk::physical_device_memory_properties inline
	get_physical_device_memory_properties(
		handle<vk::instance> instance,
		handle<vk::physical_device> physical_device
	) {
		vk::physical_device_memory_properties props;
		vk::get_instance_function<
			vk::get_physical_device_memory_properties_function
		>(
			instance
		)(
			physical_device.underlying(), &props
		);
		return props;
	}

} // vk