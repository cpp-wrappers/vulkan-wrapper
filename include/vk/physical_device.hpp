export module vk.physical_device;

import vk_headers;
export import <compare>;
export import vk.physical_device_properties;
export import vk.queue_family_properties;

vk::physical_device_properties
inline get_physical_device_properties(VkPhysicalDevice d) {
	VkPhysicalDeviceProperties props;
	vkGetPhysicalDeviceProperties(d, &props);
	return *((vk::physical_device_properties*)(&props));
}

void inline get_queue_family_properties(
	VkPhysicalDevice d,
	uint32_t* count,
	VkQueueFamilyProperties* props
) {
	vkGetPhysicalDeviceQueueFamilyProperties(d, count, props);
}

namespace vk {

export struct queue_families_properties_view {
	VkPhysicalDevice m_physical_device;

	struct iterator {
		VkPhysicalDevice m_physical_device;
		uint32_t m_family_queue;

		vk::queue_family_properties
		operator * () const {
			uint32_t size = m_family_queue + 1;

			vk::queue_family_properties props[size];

			get_queue_family_properties(
				m_physical_device,
				&size,
				(VkQueueFamilyProperties*)props
			);

			return props[m_family_queue];
		}

		auto& operator ++ () {
			++m_family_queue;
			return *this;
		}

		auto operator <=> (const iterator&) const = default;
	};

	iterator begin() const {
		return { m_physical_device, 0 };
	}

	uint32_t size() const {
		uint32_t count;
		get_queue_family_properties(
			m_physical_device,
			&count,
			nullptr
		);
		return count;
	}

	iterator end() const {
		return { m_physical_device, size() };
	}
};

export struct physical_device {
	VkPhysicalDevice m_physical_device;

	physical_device_properties properties() const {
		return get_physical_device_properties(m_physical_device);
	}

	queue_families_properties_view queue_families_properties() const {
		return { m_physical_device };
	}
	
};

}