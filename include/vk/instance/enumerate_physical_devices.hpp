#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/one_of.hpp>

#include "../shared/headers.hpp"
#include "../shared/result.hpp"
#include "../shared/ptr_to_ref_like.hpp"
#include "../shared/result.hpp"
#include "../shared/count.hpp"
#include "core/type/is_constructible_from.hpp"

namespace vk::internal {
	struct instance;
	struct physical_device;

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::internal::instance*>::equals<1>,
			types::count_of_ranges_of_value_type<vk::internal::physical_device*>::equals<1>
		>::for_types_of<Args...>
	)
	elements::one_of<vk::result, vk::count>
	try_enumerate_physical_devices(const Args&... args) {
		auto& devices = elements::range_of_value_type<vk::internal::physical_device*>::for_elements_of(args...);

		uint32 count = (uint32) devices.size();

		vk::result result {
			(uint32) vkEnumeratePhysicalDevices(
				(VkInstance) elements::of_type<vk::internal::instance* const &>::for_elements_of(args...),
				&count,
				(VkPhysicalDevice*) devices.data()
			)
		};

		if( result.success()) {
			return vk::count{ count };
		}

		return result;
	}
}