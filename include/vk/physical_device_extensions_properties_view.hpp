export module vk.physical_device_extensions_properties_view;

import vk_headers;
export import <compare>;
export import vk.extension_properties;
export import vk.result;

export namespace vk {

struct physical_device_extensions_properties_view {
	VkPhysicalDevice m_physical_device;
	const char* m_layer_name;

	struct iterator {
		VkPhysicalDevice m_physical_device;
		const char* m_layer_name = nullptr;
		uint32_t m_extension = 0;

		vk::extension_properties
		operator * () const {
			uint32_t count = m_extension + 1;
			vk::extension_properties props[count];
			
			vk::throw_if_error(
				(int) vkEnumerateDeviceExtensionProperties(
					m_physical_device,
					m_layer_name,
					&count,
					(VkExtensionProperties*)props
				)
			);
			return props[m_extension];
		}

		auto& operator ++ () {
			++m_extension;
			return *this;
		}

		auto operator ++ (int) {
			iterator copy{*this};
			++m_extension;
			return copy;
		}

		auto operator <=> (const iterator&) const = default;
	};

	iterator begin() const {
		return { m_physical_device, m_layer_name, 0 };
	}

	uint32_t size() const {
		uint32_t count;

		vk::throw_if_error(
			(int) vkEnumerateDeviceExtensionProperties(
				m_physical_device,
				m_layer_name,
				&count,
				nullptr
			)
		);

		return count;
	}

	iterator end() const {
		return { m_physical_device, m_layer_name, size() };
	}
};

}