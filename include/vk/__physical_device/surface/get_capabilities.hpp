#pragma once

#include "../handle.hpp"
#include "../../__internal/function.hpp"
#include "../../__internal/unexpected_handler.hpp"
#include "../../__surface/handle.hpp"
#include "../../__surface/capabilities.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct get_physical_device_surface_capabilities_function :
		vk::function<int32(*)(
			handle<vk::physical_device>::underlying_type physical_device,
			handle<vk::surface>::underlying_type surface,
			vk::surface_capabilities* surface_capabilities
		)>
	{
		static constexpr auto name
			= "vkGetPhysicalDeviceSurfaceCapabilitiesKHR";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::physical_device>>.decayed == 1,
		is_same_as<handle<vk::surface>>.decayed == 1
	>
	vk::expected<vk::surface_capabilities>
	try_get_physical_device_surface_capabilities(Args&&... args) {
		handle<vk::instance> instance = tuple { args... }.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::physical_device> physical_device = tuple { args... }.template
			get<is_same_as<handle<vk::physical_device>>.decayed>();

		handle<vk::surface> surface = tuple { args... }.template
			get<is_same_as<handle<vk::surface>>.decayed>();

		vk::surface_capabilities caps;

		vk::result result {
			vk::get_instance_function<
				vk::get_physical_device_surface_capabilities_function
			>(
				instance
			)(
				physical_device.underlying(),
				surface.underlying(),
				&caps
			)
		};

		if (caps.max_image_count == 0) { // attention, please.
			caps.max_image_count = uint32(0) - uint32(1);
		}

		if (result.error()) return result;

		return caps;
	}

	template<typename... Args>
	vk::surface_capabilities
	get_physical_device_surface_capabilities(Args&&... args) {
		vk::expected<vk::surface_capabilities> result
			= vk::try_get_physical_device_surface_capabilities(
				forward<Args>(args)...
			);
		if (result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk