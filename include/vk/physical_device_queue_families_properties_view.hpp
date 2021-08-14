
export module vk.physical_device_queue_families_properties_view;

import vk_headers;
export import <compare>;
export import vk.queue_family_properties;

namespace vk {

export struct physical_device_queue_families_properties_view {
	VkPhysicalDevice m_physical_device;

	physical_device_queue_families_properties_view(void* p_physical_device)
		: m_physical_device{ (VkPhysicalDevice)p_physical_device }
	{}

	struct iterator {
		VkPhysicalDevice m_physical_device;
		uint32_t m_family_queue;

		vk::queue_family_properties
		operator * () const {
			uint32_t size = m_family_queue + 1;

			vk::queue_family_properties props[size];

			vkGetPhysicalDeviceQueueFamilyProperties(
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

		auto operator ++ (int) {
			iterator copy{*this};
			++m_family_queue;
			return copy;
		}

		auto operator <=> (const iterator&) const = default;
	};

	iterator begin() const {
		return { m_physical_device, 0 };
	}

	uint32_t size() const {
		uint32_t count;
		vkGetPhysicalDeviceQueueFamilyProperties(
			m_physical_device,
			&count,
			nullptr
		);
		return count;
	}

	iterator end() const {
		return { m_physical_device, size() };
	}
}; // queue_families_properties_view

} // vk