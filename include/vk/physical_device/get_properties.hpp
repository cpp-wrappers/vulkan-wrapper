#pragma once

#include "handle.hpp"
#include "properties_2.hpp"
#include "extension_properties.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/elements/for_each_satisfying_type_predicate.hpp>

extern "C" VK_ATTR void VK_CALL vkGetPhysicalDeviceProperties(
	handle<vk::physical_device>     physical_device,
	vk::physical_device_properties* properties
);

extern "C" VK_ATTR void VK_CALL vkGetPhysicalDeviceProperties2(
	handle<vk::physical_device>       physical_device,
	vk::physical_device_properties_2* properties
);

namespace vk {

	[[ nodiscard ]]
	vk::physical_device_properties inline
	get_physical_device_properties(
		handle<vk::physical_device> physical_device
	) {
		vk::physical_device_properties props;

		vkGetPhysicalDeviceProperties(
			physical_device,
			&props
		);

		return props;
	}

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::physical_device>>,
		types::are_contain_satisfying_predicate<
			vk::is_extension_properties_reference
		>
	>::for_types<Args...>
	[[ nodiscard ]]
	vk::physical_device_properties
	get_physical_device_properties(Args&&... args) {
		vk::physical_device_properties_2 props{};

		auto physical_device = elements::decayed<
			handle<vk::physical_device>
		>(args...);

		const void** next = &props.next;

		elements::for_each_satisfying_type_predicate<
			vk::is_extension_properties_reference
		>(args...)(
			[&](auto& extension_properties) {
				*next = &extension_properties;
				next = &extension_properties.next;
			}
		);

		vkGetPhysicalDeviceProperties2(
			physical_device,
			&props
		);

		return props.properties;

	} // get_properties

} // vk

template<typename... Args>
vk::physical_device_properties
handle<vk::physical_device>::get_properties(Args&&... args) const {
	return vk::get_physical_device_properties(
		*this, forward<Args>(args)...
	);
}