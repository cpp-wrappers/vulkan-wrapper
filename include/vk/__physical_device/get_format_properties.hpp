#pragma once

#include "./handle.hpp"
#include "./format_properties.hpp"
#include "../__internal/function.hpp"
#include "../__internal/format.hpp"
#include "../__instance/handle.hpp"

namespace vk {

	struct get_physical_device_format_properties_function :
		vk::function<void(*)(
			handle<vk::physical_device>::underlying_type physical_device,
			vk::format format,
			vk::format_properties* pFormatProperties
		)
	> {
		static constexpr auto name = "vkGetPhysicalDeviceFormatProperties";
	};

	inline vk::format_properties get_physical_device_format_properties(
		handle<vk::instance> instance,
		handle<vk::physical_device> physical_device,
		vk::format format
	) {
		vk::format_properties props;

		vk::get_instance_function<
			vk::get_physical_device_format_properties_function
		>(instance)(
			physical_device.underlying(), format, &props
		);

		return props;
	}

} // vk