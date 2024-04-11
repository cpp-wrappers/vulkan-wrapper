#pragma once

#include "./properties/view_properties.hpp"

#include "../../__internal/layer_name.hpp"

namespace vk {

	inline bool is_instance_layer_supported(vk::layer_name name) {
		bool supported = false;

		vk::view_instance_layer_properties(
			[&](span<vk::layer_properties> props) {
				auto names = props.transform_view(
					[](vk::layer_properties& layer_props) {
						return vk::layer_name{ layer_props.name };
					}
				);
				for (vk::layer_name p : names) {
					if (p.has_equal_size_and_elements(name)) {
						supported = true;
						break;
					}
				}
			}
		);

		return supported;
	}

} // vk