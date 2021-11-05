#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/c_string.hpp>
#include <core/elements/range_of_value_type.hpp>

#include "../shared/extension_name.hpp"
#include "../shared/extension_properties.hpp"
#include "core/elements/of_type.hpp"
#include "core/wrapper/of_integer.hpp"

namespace vk::internal {

	struct physical_device;

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::internal::physical_device*>::equals<1>,
			types::count_of_type<vk::extension_name>::less_or_equals<1>,
			types::count_of_ranges_of_value_type<vk::extension_properties>::equals<1>
		>::for_types_of<Args...>
	)
	auto enumerate_physical_device_extension_properties(const Args&... args) {
		auto& props = elements::range_of_value_type<vk::extension_properties>::for_elements_of(args...);

		uint32 count = (uint32) props.size();

		const char* name = nullptr;
		if constexpr(types::count_of_type<vk::extension_name>::for_types_of<Args...> != 0) {
			name = elements::of_type<const vk::extension_name&>::for_elements_of(args...).begin();
		}

		uint32 vk_result = (uint32) vkEnumerateDeviceExtensionProperties(
			(VkPhysicalDevice) elements::of_type<vk::internal::physical_device* const &>::for_elements_of(args...),
			name,
			&count,
			(VkExtensionProperties*) props.data()
		);

		struct result : wrapper::of_integer<uint32> {
			uint32 count;
		};

		return result{ vk_result, count };
	}

}