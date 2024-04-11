#pragma once

#include "properties/view.hpp"

#include "../../__internal/extension_name.hpp"

namespace vk {
	
	inline bool is_instance_extension_supported(vk::extension_name name) {
		bool supported = false;

		vk::view_instance_extension_properties(
			[&](span<vk::extension_properties> props) {
				auto names = props.transform_view(
					[](vk::extension_properties& extension_props) {
						return vk::extension_name{ extension_props.name };
					}
				);

				for (vk::extension_name n : names) {
					if (n.has_equal_size_and_elements(name)) {
						supported = true;
						break;
					}
				}
			}
		);

		return supported;
	}

} // vk