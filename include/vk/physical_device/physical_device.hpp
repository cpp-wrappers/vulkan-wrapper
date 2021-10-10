#pragma once

#include "properties.hpp"
#include "../result.hpp"
#include "../surface_capabilities.hpp"
#include "../queue_family_index.hpp"
#include "queue_family_properties_view.hpp"
#include "extension_properties_view.hpp"

#include <core/forward.hpp>

namespace vk {

struct device;
struct surface;

struct physical_device {
	physical_device() = delete;
	physical_device(const physical_device&) = delete;

	physical_device_properties properties() const {
		vk::physical_device_properties props;
		vkGetPhysicalDeviceProperties(
			(VkPhysicalDevice)this,
			(VkPhysicalDeviceProperties*)&props
		);
		return props;
	}

	template<typename F>
	void view_queue_family_properties(F&& f) const {
		view_physical_device_queue_family_properties(
			(VkPhysicalDevice)this,
			forward<F>(f)
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
			(VkPhysicalDevice)this,
			"",
			forward<F>(f)
		);
	}

	void for_each_extension_properties(auto&& f) {
		view_extension_properties([&](auto& view) {
			for(auto& props : view) f(props);
		});
	}

	vk::surface_capabilities get_surface_capabilities(vk::surface& s) const {
		vk::surface_capabilities caps;

		vk::throw_if_error(
			vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
				(VkPhysicalDevice)this,
				(VkSurfaceKHR)&s,
				(VkSurfaceCapabilitiesKHR*) &caps
			)
		);

		return caps;
	}

	bool get_surface_support(vk::queue_family_index queue_family_index, vk::surface& s) {
		uint32_t result;

		vk::throw_if_error(
			vkGetPhysicalDeviceSurfaceSupportKHR(
				(VkPhysicalDevice)this,
				(primitive::uint32)queue_family_index,
				(VkSurfaceKHR)&s,
				&result
			)
		);

		return result;
	}

	template<typename F>
	void view_surface_formats(vk::surface& surface, uint32_t count, F&& f) const {
		view_physical_device_surface_formats(*this, surface, count, forward<F>(f));
	}

	template<typename F>
	void view_surface_formats(vk::surface& surface, F&& f) const {
		uint32_t count;
		
		vk::throw_if_error(
			vkGetPhysicalDeviceSurfaceFormatsKHR(
				(VkPhysicalDevice)this,
				(VkSurfaceKHR)&surface,
				&count,
				nullptr
			)
		);

		view_surface_formats<F>(surface, count, forward<F>(f));
	}
};

}