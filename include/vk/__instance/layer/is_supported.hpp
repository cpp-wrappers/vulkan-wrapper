#pragma once

#include "properties/view_properties.hpp"

#include "../../layer_name.hpp"

#include <core/contains.hpp>
#include <core/transform.hpp>

namespace vk {

	inline bool is_instance_layer_supported(vk::layer name) {
		bool supported = false;

		vk::view_instance_layer_properties(
			[&](span<vk::layer_properties> props) {
				supported = contains(name).in(
					transform_view(props, [](auto& layer_props) {
						return vk::layer{ layer_props.name };
					})
				);
			}
		);

		return supported;
	}

} // vk