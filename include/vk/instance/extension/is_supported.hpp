#pragma once

#include "properties/view.hpp"

#include "../../extension.hpp"

#include <core/contains.hpp>
#include <core/transform.hpp>

namespace vk {
	
	inline bool is_instance_extension_supported(vk::extension name) {
		bool supported = false;

		vk::view_instance_extension_properties(
			[&](span<vk::extension_properties> props) {
				supported = contains(name).in(
					transform_view(props,[](auto& extension_props) {
						return vk::extension{ extension_props.name };
					})
				);
			}
		);

		return supported;
	}

} // vk