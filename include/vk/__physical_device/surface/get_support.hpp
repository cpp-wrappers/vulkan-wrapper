#pragma once

#include "../handle.hpp"
#include "../../__instance/handle.hpp"
#include "../../__surface/handle.hpp"
#include "../../__internal/function.hpp"
#include "../../__internal/queue_family_index.hpp"
#include "../../__internal/result.hpp"
#include "../../__internal/unexpected_handler.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct get_physical_device_surface_support_function : vk::function<
		int32 (*)(
			handle<vk::physical_device>::underlying_type physical_device,
			vk::queue_family_index queue_family_index,
			handle<vk::surface>::underlying_type surface,
			uint32* supported
		)
	> {
		static constexpr auto name = "vkGetPhysicalDeviceSurfaceSupportKHR";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::physical_device>>.decayed == 1,
		is_same_as<handle<vk::surface>>.decayed == 1,
		is_same_as<vk::queue_family_index>.decayed == 1
	>
	[[ nodiscard ]]
	vk::expected<bool>
	try_get_physical_device_surface_support(Args&&... args) {
		handle<vk::instance> instance = tuple{ args... }.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::physical_device> physical_device = tuple{ args... }.template
			get<is_same_as<handle<vk::physical_device>>.decayed>();

		handle<vk::surface> surface = tuple{ args... }.template
			get<is_same_as<handle<vk::surface>>.decayed>();

		vk::queue_family_index queue_family_index = tuple{ args... }.template
			get<is_same_as<vk::queue_family_index>.decayed>();

		uint32 supports;

		vk::result result {
			vk::get_instance_function<
				vk::get_physical_device_surface_support_function
			>(instance)(
				physical_device.underlying(),
				queue_family_index,
				surface.underlying(),
				&supports
			)
		};

		if(result.error()) return result;

		return { (bool) supports };
	} // try_get_physical_device_surface_support

	template<typename... Args>
	[[ nodiscard ]]
	bool get_physical_device_surface_support(Args&&... args) {
		vk::expected<bool> result = vk::try_get_physical_device_surface_support(
			forward<Args>(args)...
		);

		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}

		return result.get_expected();
	}

} // vk