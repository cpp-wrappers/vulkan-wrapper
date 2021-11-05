#pragma once

#include <core/elements/one_of.hpp>
#include <core/wrapper/of_integer.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/of_type.hpp>

#include "../shared/result.hpp"
#include "../shared/queue_family_index.hpp"
#include "../shared/headers.hpp"

namespace vk {

	struct surface_support : wrapper::of_integer<uint32> {};

	namespace internal {

		struct physical_device;
		struct surface;

		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::count_of_type<vk::internal::physical_device>::equals<1>,
				types::count_of_type<vk::queue_family_index>::equals<1>,
				types::count_of_type<vk::internal::surface>::equals<1>
			>::for_types_of<Args...>
		)
		elements::one_of<vk::result, vk::surface_support>
		try_get_physical_device_surface_support(const Args&... args) {
			vk::surface_support s;

			vk::result result {
				(uint32) vkGetPhysicalDeviceSurfaceSupportKHR(
					(VkPhysicalDevice) & elements::of_type<const vk::internal::physical_device&>::for_elements_of(args...),
					(uint32) elements::of_type<const vk::queue_family_index&>::for_elements_of(args...),
					(VkSurfaceKHR) & elements::of_type<const vk::internal::surface&>::for_elements_of(args...),
					(VkBool32*) &s
				)
			};

			if(result.success()) {
				return s;
			}
			
			return result;
		}

	}
}