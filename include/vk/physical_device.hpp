#pragma once

#include <compare>
#include <cstddef>

#include <core/types.hpp>
#include <core/storage.hpp>
#include <vulkan/vulkan_core.h>

#include "headers.hpp"
#include "physical_device/properties.hpp"
#include "physical_device/queue_family_properties.hpp"
#include "physical_device/queue_family_properties_view.hpp"
#include "physical_device/extension_properties_view.hpp"
#include "physical_device/surface_formats_view.hpp"
#include "device_queue_create_info.hpp"
#include "device_create_info.hpp"
#include "surface_capabilities.hpp"
#include "result.hpp"
#include "queue_family_index.hpp"

namespace vk {

struct device;
struct surface;

struct physical_device {
	physical_device() = delete;
	physical_device(const physical_device&) = delete;

	template<typename... Args>
	requires(
		(
			types::of<Args...>::template contains_same_as_type<vk::enabled_extension_count>
			==
			types::of<Args...>::template contains_same_as_type<vk::enabled_extension_names>
		) &&
		types::of<Args...>::template erase_same_as_one_of_types<
			vk::device_queue_create_info, vk::enabled_extension_count, vk::enabled_extension_names
		>::empty
	)
	vk::device& create_device(Args... args) const {
		vk::device_create_info ci{};
		ci.queue_create_info_count = types::of<Args...>::template count_of_same_as_type<vk::device_queue_create_info>;

		storage<10000> dqcis_storage[ci.queue_create_info_count];
		vk::device_queue_create_info* dqcis = (vk::device_queue_create_info*)dqcis_storage;
		ci.queue_create_infos = dqcis;
		std::size_t current = 0;

		tuple{ args... }
			.get([&](vk::device_queue_create_info dqci) {
				dqcis[current++] = dqci;
			})
			.get([&](vk::enabled_extension_count c) {
				ci.enabled_extension_count = c;
			})
			.get([&](vk::enabled_extension_names n) {
				ci.enabled_extension_names = n;
			})
		;

		vk::device* device;

		vk::throw_if_error(
			vkCreateDevice(
				(VkPhysicalDevice) this,
				(VkDeviceCreateInfo*) &ci,
				nullptr,
				(VkDevice*) &device
			)
		);

		return *device;
	}

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
			(VkPhysicalDevice)this,
			"",
			std::forward<F>(f)
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
				queue_family_index.value,
				(VkSurfaceKHR)&s,
				&result
			)
		);

		return result;
	}

	template<typename F>
	void view_surface_formats(vk::surface& surface, uint32_t count, F&& f) const {
		view_physical_device_surface_formats(*this, surface, count, std::forward<F>(f));
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

		view_surface_formats<F>(surface, count, std::forward<F>(f));
	}
};

}