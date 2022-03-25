#pragma once

#include "handle.hpp"
#include "features_2.hpp"
#include "features.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/meta/decayed_same_as.hpp>

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_decayed<handle<vk::physical_device>>,
		types::are_may_contain_decayed<vk::physical_device_features>,
		types::are_may_contain_decayed_satisfying_predicate<
			vk::is_physical_device_features
		>
	>::for_types<Args...>
	void get_features(Args&&... args) {
		vk::physical_device_features_2 features{};

		if constexpr (
			types::are_contain_decayed<
				vk::physical_device_features
			>::for_types<Args...>
		) {
			features.features = elements::decayed<
				vk::physical_device_features
			>(args...);
		}

		const void** next = &features.next;

		elements::for_each_decayed_satisfying_predicate<
			vk::is_physical_device_features
		>(args...)(
			[&](auto& features) {
				*next = &features;
				next = &features.next;
			}
		);

		auto physical_device = elements::decayed<
			handle<vk::physical_device>
		>(args...);

		vkGetPhysicalDeviceFeatures2(
			(VkPhysicalDevice) vk::get_handle_value(physical_device),
			(VkPhysicalDeviceFeatures2*) &features
		);

	} // get_features

} // vk

template<typename... Args>
void handle<vk::physical_device>::get_features(Args&&... args) const {
	return vk::get_features(*this, forward<Args>(args)...);
}