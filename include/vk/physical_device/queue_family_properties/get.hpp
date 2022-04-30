#pragma once

#include "../handle.hpp"
#include "../../function.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/range_of_value_type_same_as.hpp>
#include <core/meta/decayed_same_as.hpp>

extern "C" VK_ATTR void VK_CALL vkGetPhysicalDeviceQueueFamilyProperties(
	handle<vk::physical_device>  physical_device,
	uint32*                      queue_family_property_count,
	vk::queue_family_properties* queue_family_properties
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_range_of<vk::queue_family_properties>,
		types::are_contain_decayed<handle<vk::physical_device>>
	>::for_types<Args...>
	[[ nodiscard ]]
	vk::count get_physical_device_queue_family_properties(Args&&... args) {
		auto& range = elements::range_of<vk::queue_family_properties>(args...);
		handle<vk::physical_device> physical_device {
			elements::decayed<handle<vk::physical_device>>(args...)
		};

		uint32 count = (uint32) range.size();

		vkGetPhysicalDeviceQueueFamilyProperties(
			physical_device,
			&count,
			range.data()
		);

		return { count };
	}

} // vk

template<range_of<vk::queue_family_properties> Range>
vk::count
handle<vk::physical_device>::get_queue_family_properties(Range&& range) const {
	return vk::get_physical_device_queue_family_properties(
		forward<Range>(range), *this
	);
}