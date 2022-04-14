#pragma once

#include "handle.hpp"

extern "C" VK_ATTR int32 VK_CALL vkGetPhysicalDeviceSurfaceSupportKHR(
	handle<vk::physical_device> physical_device,
	vk::queue_family_index queue_family_index,
	handle<vk::surface> surface,
	uint32* supported
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::physical_device>>,
		types::are_contain_one_decayed<handle<vk::surface>>,
		types::are_contain_one_decayed<vk::queue_family_index>
	>::for_types<Args...>
	vk::expected<bool>
	try_get_physical_device_surface_support(Args&&... args) {
		handle<vk::physical_device> physical_device = elements::decayed<
			handle<vk::physical_device>
		>(args...);

		auto surface = elements::decayed<handle<vk::surface>>(args...);

		vk::queue_family_index queue_family_index {
			elements::decayed<vk::queue_family_index>(args...)
		};

		uint32 supports;

		vk::result result {
			vkGetPhysicalDeviceSurfaceSupportKHR(
				physical_device,
				queue_family_index,
				surface,
				&supports
			)
		};

		if(result.error()) return result;

		return { (bool)supports };
	} // try_get_physical_device_surface_support

	template<typename... Args>
	bool get_physical_device_surface_support(Args&&... args) {
		auto result = vk::try_get_physical_device_surface_support(
			forward<Args>(args)...
		);

		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}

		return result.get_expected();
	}

} // vk

template<typename... Args>
bool
handle<vk::physical_device>::
get_surface_support(Args&&... args) const {
	return vk::get_physical_device_surface_support(
		*this, forward<Args>(args)...
	);
}