#pragma once

#include <types.hpp>

#include "./get_memory_properties.hpp"
#include "../__internal/memory_type_index.hpp"
#include "../__internal/unexpected_handler.hpp"

namespace vk {

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_convertible_to<handle<vk::instance>> == 1,
		is_convertible_to<handle<vk::physical_device>> == 1,
		(
			is_same_as<vk::memory_properties>.decayed == 1 ||
			is_same_as<vk::memory_property>.decayed > 0
		),
		is_same_as<vk::memory_type_indices>.decayed <= 1
	>
	vk::memory_type_index find_first_memory_type_index(Args&&... args) {
		tuple a { args... };

		auto instance = (handle<vk::instance>) a.template
			get<is_convertible_to<handle<vk::instance>>>();

		auto physical_device = (handle<vk::physical_device>) a.template
			get<is_convertible_to<handle<vk::physical_device>>>();

		vk::memory_properties required_properties;
		
		a.template pass<is_same_as<vk::memory_properties>.decayed>(
			[&](auto... properties) {
				((required_properties = properties), ...);
			}
		);
		a.template pass<is_same_as<vk::memory_property>.decayed>(
			[&](auto... property) {
				(required_properties.set(property), ...);
			}
		);

		vk::physical_device_memory_properties physical_device_memory_properties
			= vk::get_physical_device_memory_properties(
				instance, physical_device
			);

		for (
			uint32 i = 0;
			i < physical_device_memory_properties.memory_type_count;
			++i
		) {
			bool required_type = true;

			if constexpr (
				(is_same_as<vk::memory_type_indices>.decayed > 0)
				.for_types<Args...>()
			) {
				vk::memory_type_indices required_indices = a.template
					get<is_same_as<vk::memory_type_indices>.decayed>();

				required_type = required_indices.at(i);
			}

			vk::memory_type memory_type =
				physical_device_memory_properties.memory_types[i];

			bool meets_required_properties =
				(memory_type.properties & required_properties)
				== required_properties;

			if (required_type && meets_required_properties) {
				return (vk::memory_type_index) i;
			}
		}

		vk::unexpected_handler();
	}

	inline vk::memory_type_index find_first_memory_type_index(
		handle<vk::instance> instance,
		handle<vk::physical_device> physical_device,
		vk::memory_properties required_properties
	) {
		vk::physical_device_memory_properties props
			= vk::get_physical_device_memory_properties(
				instance, physical_device
			);

		vk::memory_type_indices indices;

		for (uint32 i = 0; i < props.memory_type_count; ++i) {
			indices.set(vk::memory_type_index{ i });
		}

		return vk::find_first_memory_type_index(
			instance, physical_device, required_properties, indices
		);
	}

}