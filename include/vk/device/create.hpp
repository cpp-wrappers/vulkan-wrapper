#pragma once

#include "handle.hpp"
#include "create_info.hpp"
#include "queue_create_info.hpp"
#include "../physical_device/handle.hpp"

namespace vk {
		template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::physical_device>::equals<1u>,
			types::count_of_ranges_of_value_type<vk::queue_create_info>::less_or_equals<1u>,
			types::count_of_ranges_of_value_type<vk::extension_name>::less_or_equals<1u>
		>::for_types_of<Args...>
	)
	elements::one_of<vk::result, vk::device>
	try_create_device(const Args&... args) {
		vk::device_create_info ci{};

		const vk::physical_device& physical_device = elements::of_type<const vk::physical_device&>::for_elements_of(args...);

		if constexpr(types::count_of_ranges_of_value_type<vk::queue_create_info>::equals<1u>::for_types_of<Args...>) {
			const auto& queue_create_infos = elements::range_of_value_type<vk::queue_create_info>::for_elements_of(args...);
			ci.queue_create_info_count = (uint32) queue_create_infos.size();
			ci.queue_create_infos = queue_create_infos.data();
		}
		if constexpr(types::count_of_ranges_of_value_type<vk::extension_name>::equals<1u>::for_types_of<Args...>) {
			const auto& extensions = elements::range_of_value_type<vk::extension_name>::for_elements_of(args...);
			ci.enabled_extension_count = (uint32) extensions.size();
			ci.enabled_extension_names = extensions.data();
		}

		VkDevice device;

		vk::result result {
			(uint32) vkCreateDevice(
				(VkPhysicalDevice) physical_device.handle,
				(VkDeviceCreateInfo*) &ci,
				nullptr,
				(VkDevice*) &device
			)
		};
		if(result.success()) return device;
		return result;
	}

	template<typename... Args>
	vk::device create_device(const Args&... args) {
		return try_create_device(args...).template get<vk::device>();
	}
}