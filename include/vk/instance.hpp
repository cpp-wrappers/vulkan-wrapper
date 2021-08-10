export module vk.instance;

import <cstdint>;
import <string>;
import <iostream>;
import vk_headers;
export import <optional>;
export import <compare>;
export import <cxx_util/parameter_pack/for_each.hpp>;
export import vk.application_info;
export import vk.physical_device;

inline void assert(auto v) {
	if(v < 0) {
		std::cout << v << std::endl;
		throw;
	}
}

inline void create_instance(VkInstance* m_raw, std::optional<vk::application_info> ai) {

	VkInstanceCreateInfo ci {
		VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		nullptr,
		0,
		ai.has_value() ? (VkApplicationInfo*)&ai.value() : nullptr,
		0,
		nullptr,
		0,
		nullptr
	};

	assert(vkCreateInstance(&ci, nullptr, m_raw));
}

export namespace vk {

struct physical_devices_view {
	VkInstance m_instance;

	struct iterator {
		VkInstance m_instance;
		uint32_t m_device;

		vk::physical_device operator * () const {
			uint32_t count = m_device + 1;
			VkPhysicalDevice devices[count]; // Extension

			assert(vkEnumeratePhysicalDevices(
				m_instance,
				&count,
				devices
			)); // Let's hope it's cheap

			return { devices[count - 1] };
		}

		auto& operator ++ () {
			++m_device; return *this;
		}

		auto operator ++ (int) const {
			iterator copy{ *this };
			++copy;
			return copy;
		}

		auto operator <=> (const iterator&) const = default;
	};

	iterator begin() const {
		return { m_instance, 0 };
	}

	uint32_t size() const {
		uint32_t v;
		vkEnumeratePhysicalDevices(
			m_instance,
			&v,
			nullptr
		);
		return v;
	}

	iterator end() const {
		return { m_instance, size() };
	}

	vk::physical_device front() const {
		return *begin();
	}
};

struct instance {
	VkInstance m_raw;

	~instance() {
		vkDestroyInstance(m_raw, nullptr);
	}

	template<typename... Args>
	instance(Args&&... args) {
		std::optional<vk::application_info> app_info;

		u::for_each(
			u::combined {
				[&](application_info&& i) {
					//auto* ai{ (VkApplicationInfo*) i.app_info_ptr() };
					app_info = i;
				}
			},
			std::forward<Args>(args)...
		);

		create_instance(&m_raw, app_info);
	}

	physical_devices_view physical_devices() const {
		return { m_raw };
	}

};

}