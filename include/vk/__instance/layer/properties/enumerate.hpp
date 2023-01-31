#pragma once

#include "../../../layer_properties.hpp"
#include "../../../result.hpp"
#include "../../../count.hpp"
#include "../../../function.hpp"
#include "../../../unexpected_handler.hpp"

#include <core/range_of_value_type_same_as.hpp>

extern "C" VK_ATTR int32 VK_CALL vkEnumerateInstanceLayerProperties(
	uint32*               property_count,
	vk::layer_properties* properties
);

namespace vk {

	template<range_of<vk::layer_properties> Range>
	[[ nodiscard ]]
	vk::expected<vk::count>
	try_enumerate_instance_layer_properties(Range&& layer_properties) {
		uint32 count = layer_properties.size();

		vk::result result {
			vkEnumerateInstanceLayerProperties(
				&count, layer_properties.iterator()
			)
		};

		if(result.error()) return result;

		return vk::count{ count };
	}

	template<range_of<vk::layer_properties> InstanceLayersProperties>
	[[ nodiscard ]]
	vk::count enumerate_instance_layer_properties(
		InstanceLayersProperties&& instance_layers_properties
	) {
		auto result = vk::try_enumerate_instance_layer_properties(
			forward<InstanceLayersProperties>(instance_layers_properties)
		);

		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}

		return result.get_expected();
	}

} // vk