#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>

#include "../device_queue_create_info.hpp"
#include "../enabled_extension_name.hpp"
#include "core/elements/of_type.hpp"
#include "core/elements/range_of_value_type.hpp"
#include "core/types/count_of_type.hpp"
#include "create_info.hpp"
#include "../result.hpp"
#include "vk/physical_device/physical_device.hpp"

namespace vk {

struct device;

template<typename... Args>
requires(
	types::are_exclusively_satsify_predicates<
		types::count_of_type<vk::physical_device&>::equals<1u>,
		types::count_of_ranges_of_value_type<vk::device_queue_create_info>::less_or_equals<1u>,
		types::count_of_ranges_of_value_type<vk::enabled_extension_name>::less_or_equals<1u>
	>::for_types_of<Args...>
)
vk::device& create_device(Args&&... args) {
	vk::device_create_info ci{};

	vk::physical_device& physical_device = elements::of_type<vk::physical_device&>::for_elements_of(args...);

	if constexpr(types::count_of_ranges_of_value_type<vk::device_queue_create_info>::equals<1u>::for_types_of<Args...>) {
		ci.queue_create_info_count = (primitive::uint32)(primitive::uint) elements::range_of_value_type<vk::device_queue_create_info>::for_elements_of(args...).size();
		ci.queue_create_infos = elements::range_of_value_type<vk::device_queue_create_info>::for_elements_of(args...).data();
	}
	if constexpr(types::count_of_ranges_of_value_type<vk::enabled_extension_name>::equals<1u>::for_types_of<Args...>) {
		ci.enabled_extension_count = (primitive::uint32)(primitive::uint) elements::range_of_value_type<vk::enabled_extension_name>::for_elements_of(args...).size();
		ci.enabled_extension_names = elements::range_of_value_type<vk::enabled_extension_name>::for_elements_of(args...).data();
	}

	vk::device* device;
	vk::throw_if_error(
		vkCreateDevice(
			(VkPhysicalDevice) &physical_device,
			(VkDeviceCreateInfo*) &ci,
			nullptr,
			(VkDevice*) &device
		)
	);
	return *device;
}
}