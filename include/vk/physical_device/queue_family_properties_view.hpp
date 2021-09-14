#pragma once

#include "../headers.hpp"
#include <compare>
#include "queue_family_properties.hpp"

namespace vk {

template<typename F>
inline void view_physical_device_queue_family_properties(
	void* physical_device,
	F&& f
);

class physical_device_queue_family_properties_view {
	vk::queue_family_properties* m_ptr;
	uint32_t m_size;

	physical_device_queue_family_properties_view(
		vk::queue_family_properties* p_ptr,
		uint32_t p_size
	)
		: m_ptr{ p_ptr }, m_size{ p_size }
	{}

	template<typename F>
	friend inline void view_physical_device_queue_family_properties(
		void* physical_device,
		F&& f
	);
public:

	auto begin() const {
		return m_ptr;
	}

	auto end() const {
		return m_ptr + m_size;
	}

	uint32_t size() const {
		return m_size;
	}

	uint32_t index(vk::queue_family_properties& p) const {
		return (&p - m_ptr);
	}
}; // queue_families_properties_view

template<typename F>
inline void view_physical_device_queue_family_properties(
	void* physical_device,
	F&& f
) {
	uint32_t count;
	vkGetPhysicalDeviceQueueFamilyProperties(
		(VkPhysicalDevice)physical_device,
		&count,
		nullptr
	);
	vk::queue_family_properties props[count];

	vkGetPhysicalDeviceQueueFamilyProperties(
		(VkPhysicalDevice)physical_device,
		&count,
		(VkQueueFamilyProperties*)props
	);

	physical_device_queue_family_properties_view v{ props, count };

	f(v);
}

} // vk