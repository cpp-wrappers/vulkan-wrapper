#pragma once

#include "../../../extension_properties.hpp"
#include "../../../result.hpp"
#include "../../../count.hpp"
#include "../../../function.hpp"
#include "../../../unexpected_handler.hpp"

#include <core/range_of_value_type_same_as.hpp>

extern "C" VK_ATTR int32 VK_CALL vkEnumerateInstanceExtensionProperties(
	const char*               layer_name,
	uint32*                   property_count,
	vk::extension_properties* properties
);

namespace vk {

	template<range_of<vk::extension_properties> InstanceExtensionsProperties>
	vk::expected<vk::count>
	try_enumerate_instance_extension_properties(
		InstanceExtensionsProperties&& instance_extensions_properties
	) {
		uint32 count = instance_extensions_properties.size();

		vk::result result {
			vkEnumerateInstanceExtensionProperties(
				nullptr,
				&count,
				instance_extensions_properties.data()
			)
		};

		if(result.error()) return result;

		return vk::count{ count };
	}

	template<range_of<vk::extension_properties> InstanceExtensionsProperties>
	vk::count enumerate_instance_extension_properties(
		InstanceExtensionsProperties&& instance_extensions_properties
	) {
		auto result = vk::try_enumerate_instance_extension_properties(
			forward<InstanceExtensionsProperties>(
				instance_extensions_properties
			)
		);

		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}

		return result.get_expected();
	}

} // vk