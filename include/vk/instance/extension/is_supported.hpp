#pragma once

#include "properties/view.hpp"

#include "../../extension_name.hpp"

#include <core/range/contains.hpp>
#include <core/range/transform.hpp>

namespace vk {
	
	inline bool is_instance_extension_supported(vk::extension_name name) {
		bool supported = false;

		vk::view_instance_extension_properties(
			[&](span<vk::extension_properties> props) {
				supported = range::contains(name)(
					range::transform(props)([](auto& extension_props) {
						return vk::extension_name{ extension_props.name };
					})
				);
			}
		);

		return supported;
	}

} // vk