#pragma once

extern "C" VK_ATTR int32 VK_CALL vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
	handle<vk::physical_device> physical_device,
	handle<vk::surface>         surface,
	vk::surface_capabilities*   surface_capabilities
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::surface>>,
		types::are_contain_one_decayed<handle<vk::physical_device>>
	>::for_types<Args...>
	vk::expected<vk::surface_capabilities>
	try_get_physical_device_surface_capabilities(Args&&... args) {
		auto surface {
			elements::decayed<handle<vk::surface>>(args...)
		};

		auto physical_device {
			elements::decayed<handle<vk::physical_device>>(args...)
		};

		vk::surface_capabilities caps;

		vk::result result {
			vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
				physical_device,
				surface,
				&caps
			)
		};

		if(result.error()) return result;

		return caps;
	}

	template<typename... Args>
	vk::surface_capabilities
	get_physical_device_surface_capabilities(Args&&... args) {
		auto result = vk::try_get_physical_device_surface_capabilities(
			forward<Args>(args)...
		);

		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}

		return result.get_expected();
	}

} // vk

template<typename... Args>
vk::surface_capabilities
handle<vk::physical_device>::
get_surface_capabilities(Args&&... args) const {
	return vk::get_physical_device_surface_capabilities(
		*this, forward<Args>(args)...
	);
}