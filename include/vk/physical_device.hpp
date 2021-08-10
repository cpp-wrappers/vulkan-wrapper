export module vk.physical_device;

import vk_headers;

namespace vk {

struct instance;

export struct physical_device {
	friend instance;
	VkPhysicalDevice m_physical_device;
	
};

}