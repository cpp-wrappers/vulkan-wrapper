#pragma once

#include "handle.hpp"
#include "create_info.hpp"

namespace vk {
	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::application_info>::less_or_equals<1>,
			types::count_of_ranges_of_value_type<vk::layer_name>::less_or_equals<1>,
			types::count_of_ranges_of_value_type<vk::extension_name>::less_or_equals<1>
		>::for_types_of<Args...>
	)
	elements::one_of<vk::instance, vk::result>
	try_create_instance(const Args&... args) {
		instance_create_info ici{};

		if constexpr(types::are_contain_type<vk::application_info>::for_types_of<Args...>) {
			auto& app_info = elements::of_type<const vk::application_info&>::for_elements_of(args...);
			ici.application_info = &app_info;
		}

		if constexpr(types::count_of_ranges_of_value_type<vk::extension_name>::equals<1>::for_types_of<Args...>) {
			auto& range = elements::range_of_value_type<vk::extension_name>::for_elements_of(args...);
			ici.enabled_extension_count = (uint32) range.size();
			ici.enabled_extension_names = range.data();
		}

		if constexpr(types::count_of_ranges_of_value_type<vk::layer_name>::equals<1>::for_types_of<Args...>) {
			auto& range = elements::range_of_value_type<vk::layer_name>::for_elements_of(args...);
			ici.enabled_layer_count = (uint32) range.size();
			ici.enabled_layer_names = range.data();
		}

		VkInstance instance;

		vk::result result {
			(int32) vkCreateInstance(
				(VkInstanceCreateInfo*) &ici,
				nullptr,
				(VkInstance*) &instance
			)
		};

		if(result.success()) return vk::instance{ instance };

		return result;
	}

	template<typename... Args>
	vk::instance create_instance(Args&&... args) {
		auto result = vk::try_create_instance(forward<Args>(args)...);
		if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
		return result.template get<vk::instance>();
	}
}