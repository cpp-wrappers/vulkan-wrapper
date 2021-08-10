export module vk.physical_device;

import vk_headers;
export import vk.physical_device_properties;

vk::physical_device_properties
inline get_physical_device_properties(VkPhysicalDevice d) {
	VkPhysicalDeviceProperties props;
	vkGetPhysicalDeviceProperties(d, &props);
	return *((vk::physical_device_properties*)(&props));
}

namespace vk {

struct instance;

export struct physical_device {
	friend instance;
	VkPhysicalDevice m_physical_device;

	physical_device_properties properties() const {
		return get_physical_device_properties(m_physical_device);
	}
	
};

}