#pragma once

#include "properties/view_properties.hpp"

#include "../../layer_name.hpp"

#include <core/range/contains.hpp>
#include <core/range/transform.hpp>

namespace vk {

	inline bool is_instance_layer_supported(vk::layer_name name) {
		bool supported = false;

		vk::view_instance_layer_properties(
			[&](span<vk::layer_properties> props) {
				supported = range::contains(name)(
					range::transform(props)([](auto& layer_props) {
						return vk::layer_name{ layer_props.name };
					})
				);
			}
		);

		return supported;
	}

} // vk