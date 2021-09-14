#pragma once

#include "../headers.hpp"
#include <compare>
#include "../extension_properties.hpp"
#include "../result.hpp"

namespace vk {

template<typename F>
inline void view_physical_device_extension_properties(
	void* physical_device,
	const char* layer_name,
	F&& f
);

class physical_device_extension_properties_view {
	vk::extension_properties* m_ptr;
	uint32_t m_count;

	physical_device_extension_properties_view(
		vk::extension_properties* p_ptr,
		uint32_t p_count
	)
		: m_ptr{ p_ptr }, m_count{ p_count }
	{}

	template<typename F>
	friend inline void view_physical_device_extension_properties(
		void* physical_device,
		const char* layer_name,
		F&& f
	);

public:

	auto begin() const {
		return m_ptr;
	}

	auto end() const {
		return m_ptr + m_count;
	}

	auto size() const {
		return m_count;
	}
};

template<typename F>
inline void view_physical_device_extension_properties(
	void* physical_device,
	const char* layer_name,
	F&& f
) {
	uint32_t count;
	vkEnumerateDeviceExtensionProperties(
		(VkPhysicalDevice)physical_device,
		layer_name,
		&count,
		nullptr
	);

	vk::extension_properties props[count];

	vkEnumerateDeviceExtensionProperties(
		(VkPhysicalDevice)physical_device,
		layer_name,
		&count,
		(VkExtensionProperties*)props
	);

	physical_device_extension_properties_view v{props, count};
	f(v);
}

}