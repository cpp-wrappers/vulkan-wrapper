#pragma once

#include "./handle.hpp"
#include "../__physical_device/handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/unexpected_handler.hpp"

namespace vk {
	struct enumerate_physical_devices_function : vk::function<int32(VK_PTR*)(
		handle<vk::instance>::underlying_type instance,
		uint32* physical_device_count,
		handle<vk::physical_device>::underlying_type* physical_devices
	)> {
		static constexpr auto name = "vkEnumeratePhysicalDevices";
	};
}

template<
	range_of<
		is_same_as<handle<vk::physical_device>>.decayed
	> PhysicalDevices
>
[[ nodiscard ]] vk::count
handle_interface<vk::instance>::enumerate_physical_devices(
	PhysicalDevices&& physical_devices
) const {
	uint32 count = (uint32) physical_devices.size();

	vk::result result {
		vk::get_instance_function<vk::enumerate_physical_devices_function>(
			handle<vk::instance>{ this->underlying() }
		)(
			this->underlying(),
			&count,
			(vk::physical_device**) physical_devices.iterator()
		)
	};
	if (result.error()) {
		vk::unexpected_handler(result);
	}
	return vk::count{ count };
}
