#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/one_of.hpp>

#include "queue_create_info.hpp"
#include "../shared/extension_name.hpp"
#include "create_info.hpp"
#include "../shared/result.hpp"

namespace vk::internal {

	struct physical_device;
	struct device;

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::internal::physical_device&>::equals<1u>,
			types::count_of_ranges_of_value_type<vk::internal::device_queue_create_info>::less_or_equals<1u>,
			types::count_of_ranges_of_value_type<vk::extension_name>::less_or_equals<1u>
		>::for_types_of<Args...>
	)
	elements::one_of<vk::result, vk::internal::device*>
	create_device(Args&&... args) {
		vk::internal::device_create_info ci{};

		vk::internal::physical_device& physical_device = elements::of_type<vk::internal::physical_device&>::for_elements_of(args...);

		if constexpr(types::count_of_ranges_of_value_type<vk::internal::device_queue_create_info>::equals<1u>::for_types_of<Args...>) {
			auto& queue_create_infos = elements::range_of_value_type<vk::internal::device_queue_create_info>::for_elements_of(args...);
			ci.queue_create_info_count = (uint32) queue_create_infos.size();
			ci.queue_create_infos = queue_create_infos.data();
		}
		if constexpr(types::count_of_ranges_of_value_type<vk::extension_name>::equals<1u>::for_types_of<Args...>) {
			auto& extensions = elements::range_of_value_type<vk::extension_name>::for_elements_of(args...);
			ci.enabled_extension_count = (uint32) extensions.size();
			ci.enabled_extension_names = extensions.data();
		}

		vk::internal::device* device;
		vk::result result {
			vkCreateDevice(
				(VkPhysicalDevice) &physical_device,
				(VkDeviceCreateInfo*) &ci,
				nullptr,
				(VkDevice*) &device
			)
		};
		if(result.success()) return device;
		return result;
	}
}