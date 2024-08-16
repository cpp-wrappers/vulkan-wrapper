#pragma once

#include "../../handle.hpp"
#include "../../../__internal/function.hpp"
#include "../../../__internal/unexpected_handler.hpp"
#include "../../../__internal/result.hpp"
#include "../../../__surface/handle.hpp"
#include "../../../__surface/format.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct get_physical_device_surface_formats : vk::function<int32(*)(
		handle<vk::physical_device>::underlying_type physical_device,
		handle<vk::surface>::underlying_type surface,
		uint32* surface_format_count,
		vk::surface_format* surface_formats
	)> {
		static constexpr auto name = "vkGetPhysicalDeviceSurfaceFormatsKHR";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::physical_device>>.decayed == 1,
		is_same_as<handle<vk::surface>>.decayed == 1,
		is_range_of<is_same_as<vk::surface_format>.decayed> == 1
	>
	[[ nodiscard ]]
	vk::expected<vk::count>
	try_get_physical_device_surface_formats(Args&&... args) {
		handle<vk::instance> instance = tuple{ args... }.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::physical_device> physical_device = tuple{ args... }.template
			get<is_same_as<handle<vk::physical_device>>.decayed>();

		handle<vk::surface> surface = tuple{ args... }.template
			get<is_same_as<handle<vk::surface>>.decayed>();

		auto& range = tuple{ args... }.template
			get<is_range_of<is_same_as<vk::surface_format>.decayed>>();

		uint32 count = (uint32) range.size();

		vk::result result {
			vk::get_instance_function<vk::get_physical_device_surface_formats>(
				instance
			)(
				physical_device.underlying(),
				surface.underlying(),
				&count,
				range.iterator()
			)
		};

		if (result.error()) return result;

		return vk::count{ count };
	}

	template<typename... Args>
	[[ nodiscard ]]
	vk::count
	get_physical_device_surface_formats(Args&&... args) {
		vk::expected<vk::count> result =
			vk::try_get_physical_device_surface_formats(forward<Args>(args)...);

		if (result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}

		return result.get_expected();
	}

} // vk