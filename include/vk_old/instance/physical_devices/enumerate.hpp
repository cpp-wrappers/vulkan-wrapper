#pragma once

#include "../handle.hpp"
#include "../../function.hpp"

extern "C" VK_ATTR int32 VK_CALL vkEnumeratePhysicalDevices(
	handle<vk::instance>         instance,
	uint32*                      physical_device_count,
	handle<vk::physical_device>* physical_devices
);

namespace vk {

	template<range_of<handle<vk::physical_device>> PhysicalDevices>
	[[ nodiscard ]]
	vk::expected<vk::count>
	try_enumerate_physical_devices(
		handle<vk::instance> instance,
		PhysicalDevices&& physical_devices
	) {
		uint32 count = (uint32) physical_devices.size();

		vk::result result {
			vkEnumeratePhysicalDevices(
				instance,
				&count,
				physical_devices.data()
			)
		};

		if(result.error()) return result;

		return vk::count{ count };
	}

	template<range_of<handle<vk::physical_device>> PhysicalDevices>
	[[ nodiscard ]]
	vk::count
	enumerate_physical_devices(
		handle<vk::instance> instance,
		PhysicalDevices&& physical_devices
	) {
		auto result {
			vk::try_enumerate_physical_devices(
				instance,
				forward<PhysicalDevices>(physical_devices)
			)
		};

		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}

		return result.get_expected();
	}

} // vk

template<range_of<handle<vk::physical_device>> PhysicalDevices>
vk::count
handle<vk::instance>::enumerate_physical_devices(
	PhysicalDevices&& physical_devices
) const {
	return vk::enumerate_physical_devices(
		*this,
		forward<PhysicalDevices>(physical_devices)
	);
}