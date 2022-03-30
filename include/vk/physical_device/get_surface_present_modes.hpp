#pragma once

#include "handle.hpp"

extern "C" VK_ATTR int32 VK_CALL vkGetPhysicalDeviceSurfacePresentModesKHR(
	handle<vk::physical_device> physical_device,
	handle<vk::surface> surface,
	uint32* present_mode_count,
	vk::present_mode* present_modes
);

namespace vk {
	
	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::physical_device>>,
		types::are_contain_one_possibly_guarded_handle_of<vk::surface>,
		types::are_contain_range_of<vk::present_mode>
	>::for_types<Args...>
	vk::expected<vk::count>
	try_get_physical_device_surface_present_modes(Args&&... args) {
		handle<vk::physical_device> physical_device = elements::decayed<
			handle<vk::physical_device>
		>(args...);

		auto& surface = elements::possibly_guarded_handle_of<
			vk::surface
		>(args...);

		auto& range = elements::range_of<vk::present_mode>(args...);

		uint32 count = (uint32) range.size();

		vk::result result {
			vkGetPhysicalDeviceSurfacePresentModesKHR(
				physical_device,
				vk::get_handle(surface),
				&count,
				range.data()
			)
		};

		if(result.error()) return result;

		return vk::count{ count };
	}

	template<typename... Args>
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
handle<vk::physical_device>::
get_surface_present_modes(Args&&... args) const {
	return vk::get_physical_device_surface_present_modes(
		*this, forward<Args>(args)...
	);
}

template<possibly_guarded_handle_of<vk::surface> Surface>
vk::count
handle<vk::physical_device>::
get_surface_present_mode_count(Surface& surface) const {
	return get_surface_present_modes(surface, span<vk::present_mode>{ nullptr, 0 });
}

template<possibly_guarded_handle_of<vk::surface> Surface, typename F>
vk::count
handle<vk::physical_device>::
view_surface_present_modes(Surface& surface, vk::count count, F&& f) const {
	vk::present_mode present_modes[(uint32) count];
	count = get_surface_present_modes(surface, span{ present_modes, (uint32) count });
	f(span{ present_modes, (uint32) count});
	return count;
}

template<possibly_guarded_handle_of<vk::surface> Surface, typename F>
vk::count
handle<vk::physical_device>::
view_surface_present_modes(Surface& surface, F&& f) const {
	return view_surface_present_modes(
		surface,
		get_surface_present_mode_count(surface),
		forward<F>(f)
	);
}


template<possibly_guarded_handle_of<vk::surface> Surface, typename F>
vk::count
handle<vk::physical_device>::
for_each_surface_presesnt_mode(Surface& surface, F&& f) const {
	return view_surface_present_modes(surface, [&](auto view) {
		for(auto present_mode : view) {
			f(present_mode);
		}
	});
}