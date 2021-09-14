#pragma once

#include "../headers.hpp"
#include "../ptr_to_ref_like.hpp"
#include "../result.hpp"

namespace vk {

struct physical_device;

template<typename F>
void view_instance_physical_devices(uint32_t, VkInstance, F&&);

class physical_devices_view {
	cursed::ptr_to_ref_like<vk::physical_device> m_physical_devices_begin;
	uint32_t m_count;

	physical_devices_view(
		cursed::ptr_to_ref_like<vk::physical_device> p_physical_devices_begin,
		uint32_t p_count
	)
		:
		m_physical_devices_begin {
			p_physical_devices_begin
		},
		m_count {
			p_count
		}
	{}

	template<typename F>
	friend void vk::view_instance_physical_devices(uint32_t, VkInstance, F&&);
public:

	auto begin() const {
		return m_physical_devices_begin;
	}

	auto end() const {
		return m_physical_devices_begin + m_count;
	}

	uint32_t size() const {
		return m_count;
	}

	vk::physical_device& front() const {
		return *begin();
	}
}; // physical_devices_view

template<typename F>
void view_instance_physical_devices(uint32_t count, VkInstance instance, F&& f) {
	vk::physical_device* devices[count];

	vk::throw_if_error(
		vkEnumeratePhysicalDevices(
			instance,
			&count,
			(VkPhysicalDevice*)devices
		)
	);

	physical_devices_view v {
		devices,
		count
	};
	f(v);
}

} // vk