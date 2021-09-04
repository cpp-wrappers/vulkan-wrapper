#pragma once

#include "core/types.hpp"
#include "headers.hpp"
#include <compare>
#include <cstddef>
#include <vulkan/vulkan_core.h>
#include "physical_device_properties.hpp"
#include "queue_family_properties.hpp"
#include "physical_device_queue_family_properties_view.hpp"
#include "physical_device_extension_properties_view.hpp"
#include "device.hpp"
#include "device_queue_create_info.hpp"
#include "device_create_info.hpp"
#include "result.hpp"
#include <core/storage.hpp>

namespace vk {

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

		VkDevice device;

		vk::throw_if_error(
			vkCreateDevice(
				(VkPhysicalDevice)this,
				(VkDeviceCreateInfo*)&ci,
				nullptr,
				&device
			)
		);

		return *((vk::device*)device);
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
};

}