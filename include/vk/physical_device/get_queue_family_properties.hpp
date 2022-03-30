#pragma once

#include "handle.hpp"
#include "../function.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/range/of_value_type_same_as.hpp>
#include <core/meta/decayed_same_as.hpp>

extern "C" VK_ATTR void VK_CALL vkGetPhysicalDeviceQueueFamilyProperties(
	handle<vk::physical_device> physical_device,
	uint32* queue_family_property_count,
	vk::queue_family_properties* queue_family_properties
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_range_of<vk::queue_family_properties>,
		types::are_contain_decayed<handle<vk::physical_device>>
	>::for_types<Args...>
	vk::count get_physical_device_queue_family_properties(Args&&... args) {
		auto& range = elements::range_of<vk::queue_family_properties>(args...);
		handle<vk::physical_device> physical_device =
			elements::decayed<handle<vk::physical_device>>(args...);

		uint32 count = (uint32) range.size();

		vkGetPhysicalDeviceQueueFamilyProperties(
			physical_device,
			&count,
			range.data()
		);

		return { count };
	}

} // vk

template<range::of<vk::queue_family_properties> Range>
vk::count
handle<vk::physical_device>::get_queue_family_properties(Range&& range) const {
	return vk::get_physical_device_queue_family_properties(
		forward<Range>(range), *this
	);
}

vk::count inline
handle<vk::physical_device>::
queue_family_properties_count() const {
	return get_queue_family_properties(
		span<vk::queue_family_properties>{ nullptr, 0 }
	);
}

vk::count
handle<vk::physical_device>::
view_queue_family_properties(vk::count count, auto&& f) const {
	vk::queue_family_properties props[(uint32) count];
	count = get_queue_family_properties(span{ props, (uint32) count });
	f(span{ props, (uint32) count });
	return count;
}

template<typename F>
vk::count
handle<vk::physical_device>::
view_queue_family_properties(F&& f) const {
	return view_queue_family_properties(
		queue_family_properties_count(),
		forward<F>(f)
	);
}

template<typename F>
vk::count
handle<vk::physical_device>::
view_extension_properties(F&& f, vk::layer_name name) const {
	vk::count count = get_extension_properties_count(name);
	return view_extension_properties(
		count,
		forward<F>(f),
		name
	);
}

vk::count
handle<vk::physical_device>::
for_each_extension_properties(auto&& f) const {
	return view_extension_properties([&](auto view) {
		for(auto props : view) f(props);
	});
}