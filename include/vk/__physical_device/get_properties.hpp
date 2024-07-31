#pragma once

#include "./handle.hpp"
#include "./properties.hpp"
#include "./properties_2.hpp"
#include "./extension_properties.hpp"
#include "../__internal/function.hpp"
#include "../__instance/handle.hpp"

#include "./extension_properties/acceleration_structure.hpp"
#include "./extension_properties/ray_tracing_pipeline.hpp"

namespace vk {

	struct get_physical_device_properties_function : vk::function<void(*)(
		handle<vk::physical_device>::underlying_type physical_device,
		vk::physical_device_properties* properties
	)> {
		static constexpr auto name = "vkGetPhysicalDeviceProperties";
	};

	[[ nodiscard ]]
	vk::physical_device_properties inline get_physical_device_properties(
		handle<vk::instance> instance,
		handle<vk::physical_device> physical_device
	) {
		vk::physical_device_properties props;

		vk::get_instance_function<vk::get_physical_device_properties_function>(
			instance
		)(
			physical_device.underlying(),
			&props
		);

		return props;
	}

	struct get_physical_device_properties_2_function : vk::function<void(*)(
		handle<vk::physical_device>::underlying_type physical_device,
		vk::physical_device_properties_2* properties
	)> {
		static constexpr auto name = "vkGetPhysicalDeviceProperties2";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::physical_device>>.decayed == 1,
		(vk::is_extension_properties_reference > 0)
	>
	[[ nodiscard ]]
	vk::physical_device_properties
	get_physical_device_properties_2(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::physical_device> physical_device = a.template
			get<is_same_as<handle<vk::physical_device>>.decayed>();

		vk::physical_device_properties_2 props{};

		const void** next = &props.next;

		a.for_each([&]<typename Arg>(Arg& arg) {
			if constexpr(
				vk::is_extension_properties_reference.for_type<Arg>()
			) {
				*next = &arg;
				next = &arg.next;
			}
		});

		vk::get_instance_function<
			vk::get_physical_device_properties_2_function
		> (
			instance
		)(
			physical_device.underlying(),
			&props
		);

		return props.properties;

	} // get_properties

} // vk