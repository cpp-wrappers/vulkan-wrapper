#pragma once

#include "headers.hpp"
#include <compare>
#include <vulkan/vulkan_core.h>
#include "physical_device_properties.hpp"
#include "queue_family_properties.hpp"
#include "physical_device_queue_family_properties_view.hpp"
#include "physical_device_extension_properties_view.hpp"

namespace vk {

struct physical_device {
	VkPhysicalDevice m_physical_device;

	physical_device_properties properties() const {
		vk::physical_device_properties props;
		vkGetPhysicalDeviceProperties(
			m_physical_device,
			(VkPhysicalDeviceProperties*)&props
		);
		return props;
	}

	template<typename F>
	void view_queue_family_properties(F&& f) const {
		view_physical_device_queue_family_properties(
			(void*)m_physical_device,
			std::forward<F>(f)
		);
	}

	void for_each_queue_family_properties(auto&& f) {
		view_queue_family_properties([&](auto& view) {
			for(auto& props : view) f(props);
		});
	}

	template<typename F>
	void view_extension_properties(F&& f) const {
		view_physical_device_extension_properties(
			(void*)m_physical_device,
			"",
			std::forward<F>(f)
		);
	}

	void for_each_extension_properties(auto&& f) {
		view_extension_properties([&](auto& view) {
			for(auto& props : view) f(props);
		});
	}
};

}

static_assert(sizeof(vk::physical_device) == sizeof(VkPhysicalDevice));