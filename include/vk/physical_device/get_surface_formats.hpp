#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/wrapper/of_integer.hpp>

#include "../surface/format.hpp"

namespace vk::internal {
	struct physical_device;
	struct surface;

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::internal::physical_device>::equals<1>,
			types::count_of_type<vk::internal::surface>::equals<1>,
			types::count_of_ranges_of_value_type<vk::surface_format>::equals<1>
		>::for_types_of<Args...>
	)
	auto get_physical_device_surface_formats(const Args&... args) {
		auto& props = elements::range_of_value_type<vk::surface_format>::for_elements_of(args...);

		uint32 count = (uint32) props.size();

		uint32 vk_result = (uint32) vkGetPhysicalDeviceSurfaceFormatsKHR(
			(VkPhysicalDevice) & elements::of_type<const vk::internal::physical_device&>::for_elements_of(args...),
			(VkSurfaceKHR) & elements::of_type<const vk::internal::surface&>::for_elements_of(args...),
			&count,
			(VkSurfaceFormatKHR*) props.data()
		);

		struct result : wrapper::of_integer<uint32>{
			uint32 count;
		};

		return result{ vk_result, count };
	}
}