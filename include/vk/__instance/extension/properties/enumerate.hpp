#pragma once

#include <range.hpp>
#include "../../../__internal/extension_properties.hpp"
#include "../../../__internal/result.hpp"
#include "../../../__internal/count.hpp"
#include "../../../__internal/function.hpp"
#include "../../../__internal/unexpected_handler.hpp"

namespace vk {

	struct enumerate_instance_extension_properties_function :
		vk::function<int32(*)(
			const char*               layer_name,
			uint32*                   property_count,
			vk::extension_properties* properties
		)
	>{
		static constexpr auto name = "vkEnumerateInstanceExtensionProperties";
	};

	template<
		range_of<
			is_same_as<vk::extension_properties>.decayed
		> InstanceExtensionsProperties
	>
	vk::expected<vk::count>
	try_enumerate_instance_extension_properties(
		InstanceExtensionsProperties&& instance_extensions_properties
	) {
		uint32 count = instance_extensions_properties.size();

		vk::result result {
			vk::get_global_function<
				vk::enumerate_instance_extension_properties_function
			>()(
				nullptr,
				&count,
				instance_extensions_properties.iterator()
			)
		};

		if (result.error()) {
			return result;
		}

		return vk::count{ count };
	}

	template<
		range_of<
			is_same_as<vk::extension_properties>.decayed
		> InstanceExtensionsProperties
	>
	vk::count enumerate_instance_extension_properties(
		InstanceExtensionsProperties&& instance_extensions_properties
	) {
		auto result = vk::try_enumerate_instance_extension_properties(
			forward<InstanceExtensionsProperties>(
				instance_extensions_properties
			)
		);

		if (result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}

		return result.get_expected();
	}

} // vk