#pragma once

#include "./get_memory_properties.hpp"
#include "../__internal/memory_type_index.hpp"
#include "../__internal/unexpected_handler.hpp"

namespace vk {

	inline vk::memory_type_index find_first_memory_type_index(
		handle<vk::instance> instance,
		handle<vk::physical_device> physical_device,
		vk::memory_properties required_properties,
		vk::memory_type_indices required_indices
	) {
		vk::physical_device_memory_properties physical_device_memory_properties
			= vk::get_physical_device_memory_properties(
				instance, physical_device
			);

		for(
			uint32 i = 0;
			i < physical_device_memory_properties.memory_type_count;
			++i
		) {
			bool required_type = required_indices.at(i);
			auto memory_type =
				physical_device_memory_properties.memory_types[i];

			bool meets_required_properties =
				(memory_type.properties & required_properties)
				== required_properties;

			if(required_type && meets_required_properties) {
				return (vk::memory_type_index) i;
			}
		}

		vk::unexpected_handler();
	}

}