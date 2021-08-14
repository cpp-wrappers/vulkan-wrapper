export module vk.physical_device;

import vk_headers;
export import <compare>;
export import vk.physical_device_properties;
export import vk.queue_family_properties;
export import vk.physical_device_queue_families_properties_view;
export import vk.physical_device_extensions_properties_view;

vk::physical_device_properties
inline get_physical_device_properties(VkPhysicalDevice d) {
	VkPhysicalDeviceProperties props;
	vkGetPhysicalDeviceProperties(d, &props);
	return *((vk::physical_device_properties*)(&props));
}

namespace vk {

export struct physical_device {
	VkPhysicalDevice m_physical_device;

	physical_device_properties properties() const {
		return get_physical_device_properties(m_physical_device);
	}

	physical_device_queue_families_properties_view
	queue_families_properties() const {
		return { m_physical_device };
	}

	physical_device_extensions_properties_view
	extensions_properties() const {
		return { m_physical_device, "" };
	}
};

}