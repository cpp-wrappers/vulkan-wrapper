#pragma once

#include "handle.hpp"
#include "../function.hpp"
#include "../layer_name.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/range/of_value_type_same_as.hpp>

extern "C" VK_ATTR int32 VK_CALL vkEnumerateDeviceExtensionProperties(
	handle<vk::physical_device> physical_device,
	vk::layer_name layer_name,
	uint32* property_count,
	vk::extension_properties* properties
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::physical_device>>,
		types::are_contain_ranges_of<vk::extension_properties>,
		types::are_may_contain_one_decayed<vk::layer_name>
	>::for_types<Args...>
	vk::expected<vk::count>
	try_enumerate_extension_properties(Args&&... args) {
		auto& range = elements::range_of<vk::extension_properties>(args...);

		handle<vk::physical_device> physical_device
			= elements::decayed<handle<vk::physical_device>>(args...);

		uint32 count = (uint32) range.size();
		vk::layer_name layer{};

		if constexpr (
			types::are_contain_decayed<vk::layer_name>::for_types<Args...>
		) { layer = elements::decayed<vk::layer_name>(args...); }

		vk::result result {
			vkEnumerateDeviceExtensionProperties(
				physical_device,
				layer,
				&count,
				range.data()
			)
		};

		if(result.error()) return result;

		return vk::count{ count };
	}

	template<typename... Args>
	vk::count enumerate_extension_properties(Args&&... args) {
		auto result = vk::try_enumerate_extension_properties(
			forward<Args>(args)...
		);

		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}

		return result.get_expected();
	}

} // vk

template<typename... Args>
vk::count
handle<vk::physical_device>::
enumerate_extension_properties(Args&&... args) const {
	return vk::enumerate_extension_properties(
		*this,
		forward<Args>(args)...
	);
}

vk::count inline
handle<vk::physical_device>::
get_extension_properties_count(vk::layer_name name) const {
	return enumerate_extension_properties(
		span<vk::extension_properties>{ nullptr, 0 }, name
	);
}

vk::count
handle<vk::physical_device>::
view_extension_properties(
	vk::count count,
	auto&& f,
	vk::layer_name name
) const {
	vk::extension_properties props[(uint32) count];
	count = enumerate_extension_properties(span{ props, (uint32) count }, name);
	f(span{ props, (uint32) count });
	return count;
}