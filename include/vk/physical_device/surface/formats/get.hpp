#pragma once

#include "../../handle.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

extern "C" VK_ATTR int32 VK_CALL vkGetPhysicalDeviceSurfaceFormatsKHR(
	handle<vk::physical_device> physical_device,
	handle<vk::surface>         surface,
	uint32*                     surface_format_count,
	vk::surface_format*         surface_formats
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::surface>>,
		types::are_contain_one_decayed<handle<vk::physical_device>>,
		types::are_contain_range_of<vk::surface_format>
	>::for_types<Args...>
	[[ nodiscard ]]
	vk::expected<vk::count>
	try_get_physical_device_surface_formats(Args&&... args) {
		auto surface {
			elements::decayed<handle<vk::surface>>(args...)
		};

		auto physical_device {
			elements::decayed<handle<vk::physical_device>>(args...)
		};

		auto& range = elements::range_of<vk::surface_format>(args...);

		uint32 count = (uint32) range.size();

		vk::result result {
			vkGetPhysicalDeviceSurfaceFormatsKHR(
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
	vk::count
	get_physical_device_surface_formats(Args&&... args) {
		auto result = vk::try_get_physical_device_surface_formats(
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
handle<vk::physical_device>::get_surface_formats(Args&&... args) const {
	return vk::get_physical_device_surface_formats(
		*this, forward<Args>(args)...
	);
}