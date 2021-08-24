#pragma once

#include "headers.hpp"
#include "physical_device.hpp"

namespace vk {

template<typename F>
void view_instance_physical_devices(uint32_t, VkInstance, F&&);

class physical_devices_view {
	VkInstance m_instance;
	vk::physical_device* m_physical_devices;
	uint32_t m_count;

	physical_devices_view(
		VkInstance p_instance,
		vk::physical_device* p_physical_devices,
		uint32_t p_count
	)
		: m_instance{ p_instance }, m_physical_devices{ p_physical_devices }, m_count{ p_count }
	{}

	template<typename F>
	friend void vk::view_instance_physical_devices(uint32_t, VkInstance, F&&);
public:

	auto begin() const {
		return m_physical_devices;
	}

	auto end() const {
		return m_physical_devices + m_count;
	}

	uint32_t size() const {
		return m_count;
	}

	vk::physical_device front() const {
		return *begin();
	}
}; // physical_devices_view

template<typename F>
void view_instance_physical_devices(uint32_t count, VkInstance instance, F&& f) {
	vk::physical_device devices[count];

	vk::throw_if_error(
		vkEnumeratePhysicalDevices(
			instance,
			&count,
			(VkPhysicalDevice*)devices
		)
	);

	physical_devices_view v{instance, devices, count};
	f(v);
}

} // vk