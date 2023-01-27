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
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::surface>> == 1,
		count_of_decayed_same_as<handle<vk::physical_device>> == 1
	>
	vk::expected<vk::surface_capabilities>
	try_get_physical_device_surface_capabilities(Args&&... args) {
		handle<vk::instance> instance = tuple{ args... }.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::physical_device> physical_device = tuple{ args... }.template
			get_decayed_same_as<handle<vk::physical_device>>();

		handle<vk::surface> surface = tuple{ args... }.template
			get_decayed_same_as<handle<vk::surface>>();

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

		if(result.error()) return result;

		return caps;
	}

	template<typename... Args>
	vk::surface_capabilities
	get_physical_device_surface_capabilities(Args&&... args) {
		vk::expected<vk::surface_capabilities> result
			= vk::try_get_physical_device_surface_capabilities(
				forward<Args>(args)...
			);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk