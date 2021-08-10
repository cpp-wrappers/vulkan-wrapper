export module vk.device;

import vk_headers;

export namespace vk {

struct device {
	VkDevice m_device;

	template<typename... Args>
	device(Args&&... args) {
		
	}

};

}