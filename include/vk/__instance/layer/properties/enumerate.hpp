#pragma once

#include "../../../__internal/result.hpp"
#include "../../../__internal/count.hpp"
#include "../../../__internal/unexpected_handler.hpp"
#include "../../../__internal/function.hpp"
#include "../../../__internal/layer_properties.hpp"

namespace vk {

	struct enumerate_instance_layer_properties_function : vk::function<int32(*)(
		uint32*,
		vk::layer_properties* properties
	)> {
		static constexpr auto name = "vkEnumerateInstanceLayerProperties";
	};

	template<range_of_decayed<vk::layer_properties> Range>
	[[ nodiscard ]]
	vk::expected<vk::count>
	try_enumerate_instance_layer_properties(
		Range&& layer_properties
	) {
		uint32 count = layer_properties.size();

		vk::result result {
			vk::get_global_function<
				enumerate_instance_layer_properties_function
			>()(&count, (vk::layer_properties*) layer_properties.iterator())
		};

		if (result.error()) {
			return result;
		}

		return vk::count{ count };
	}

	template<range_of_decayed<vk::layer_properties> InstanceLayersProperties>
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