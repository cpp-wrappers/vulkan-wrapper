#pragma once

#include "./handle.hpp"
#include "./features_2.hpp"
#include "./features.hpp"
#include "../__internal/function.hpp"
#include "../__instance/handle.hpp"

namespace vk {

	struct get_physical_device_features_2_function : vk::function<void(*)(
		handle<vk::physical_device>::underlying_type physical_device,
		vk::physical_device_features_2* features
	)> {
		static constexpr auto name = "vkGetPhysicalDeviceFeatures2";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::physical_device>> == 1,
		count_of_decayed_same_as<vk::physical_device_features> <= 1,
		(count_of_satisfying_predicate<
			vk::is_physical_device_features
		> > 0)
	>
	vk::physical_device_features
	get_physical_device_features_2(Args&&... args) {
		tuple a { args... };
		vk::physical_device_features_2 features2{};

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::physical_device_features> > 0
		) {
			features2.features = a.template
				get_decayed_same_as<vk::physical_device_features>();
		}

		const void** next = &features2.next;

		a.for_each([&]<typename Arg>(Arg& arg) {
			if constexpr(is_physical_device_features.for_type<Arg>()) {
				*next = &arg;
				next = &arg.next;
			}
		});

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::physical_device> physical_device = a.template
			get_decayed_same_as<handle<vk::physical_device>>();

		vk::get_instance_function<vk::get_physical_device_features_2_function>(
			instance
		)(
			physical_device.underlying(),
			&features2
		);

		return features2.features;
	} // get_features

} // vk