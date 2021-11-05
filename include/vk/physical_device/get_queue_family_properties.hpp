#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/elements/of_type.hpp>

#include "queue_family_properties.hpp"

namespace vk::internal {

	struct physical_device;


	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::internal::physical_device*>::equals<1>,
			types::count_of_ranges_of_value_type<vk::queue_family_properties>::ignore_reference::equals<1>
		>::for_types_of<Args...>
	)
	auto get_physical_device_queue_family_properties(const Args&... args) {
		auto& props = elements::range_of_value_type<vk::queue_family_properties>::for_elements_of(args...);

		uint32 count = (uint32) props.size();

		vkGetPhysicalDeviceQueueFamilyProperties(
			(VkPhysicalDevice) elements::of_type<vk::internal::physical_device* const &>::for_elements_of(args...),
			&count,
			(VkQueueFamilyProperties*) props.data()
		);

		return count;
	}
}