#pragma once

#include "../../handle.hpp"
#include "../../../function.hpp"

extern "C" VK_ATTR int32 VK_CALL vkGetPhysicalDeviceSurfacePresentModesKHR(
	handle<vk::physical_device> physical_device,
	handle<vk::surface>         surface,
	uint32*                     present_mode_count,
	vk::present_mode*           present_modes
);

namespace vk {
	
	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::physical_device>>,
		types::are_contain_one_decayed<handle<vk::surface>>,
		types::are_contain_range_of<vk::present_mode>
	>::for_types<Args...>
	[[ nodiscard ]]
	vk::expected<vk::count>
	try_get_physical_device_surface_present_modes(Args&&... args) {
		auto physical_device {
			elements::decayed<handle<vk::physical_device>>(args...)
		};

		auto surface = elements::decayed<handle<vk::surface>>(args...);

		auto& range = elements::range_of<vk::present_mode>(args...);

		uint32 count = (uint32) range.size();

		vk::result result {
			vkGetPhysicalDeviceSurfacePresentModesKHR(
				physical_device,
				surface,
				&count,
				range.data()
			)
		};

		if(result.error()) return result;

		return vk::count{ count };
	}

	template<typename... Args>
	[[ nodiscard ]]
	vk::count get_physical_device_surface_present_modes(Args&&... args) {
		auto result = vk::try_get_physical_device_surface_present_modes(
			forward<Args>(args)...
		);

		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}

		return result.get_expected();
	}

} // vk

template<typename... Args>
vk::count
handle<vk::physical_device>::get_surface_present_modes(Args&&... args) const {
	return vk::get_physical_device_surface_present_modes(
		*this, forward<Args>(args)...
	);
}