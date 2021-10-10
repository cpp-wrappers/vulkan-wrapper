#pragma once

#include "../headers.hpp"
#include "core/primitive_integer.hpp"
#include "queue_family_properties.hpp"

namespace vk {

struct physical_device;

template<typename F>
inline void view_physical_device_queue_family_properties(
	const vk::physical_device& physical_device,
	F&& f
);

class physical_device_queue_family_properties_view {
	vk::queue_family_properties* m_ptr;
	uint32 m_size;

	physical_device_queue_family_properties_view(
		vk::queue_family_properties* p_ptr,
		uint32 p_size
	)
		: m_ptr{ p_ptr }, m_size{ p_size }
	{}

	template<typename F>
	friend inline void view_physical_device_queue_family_properties(
		const vk::physical_device& physical_device,
		F&& f
	);
public:

	auto begin() const {
		return m_ptr;
	}

	auto end() const {
		return m_ptr + (primitive::uint32)m_size;
	}

	uint32 size() const {
		return m_size;
	}
}; // queue_families_properties_view

template<typename F>
inline void view_physical_device_queue_family_properties(
	const vk::physical_device& physical_device,
	F&& f
) {
	uint32 count;
	vkGetPhysicalDeviceQueueFamilyProperties(
		(VkPhysicalDevice) &physical_device,
		(primitive::uint32*) &count,
		nullptr
	);
	vk::queue_family_properties props[(primitive::uint32) count];

	vkGetPhysicalDeviceQueueFamilyProperties(
		(VkPhysicalDevice) &physical_device,
		(primitive::uint32*) &count,
		(VkQueueFamilyProperties*)props
	);

	physical_device_queue_family_properties_view v{ props, count };

	f(v);
}

} // vk