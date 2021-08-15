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

	template<typename F>
	void view_queue_families_properties(F&& f) const {
		view_physical_device_queue_families_properties(
			(void*)m_physical_device,
			std::forward<F>(f)
		);
	}

	template<typename F>
	void view_extensions_properties(F&& f) const {
		view_physical_device_extensions_properties(
			(void*)m_physical_device,
			"",
			std::forward<F>(f)
		);
	}
};

}