#pragma once

#include <core/types/count_of_type.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/elements/one_of.hpp>
#include <core/move.hpp>

#include "application_info.hpp"
#include "create_info.hpp"
#include "../shared/result.hpp"

namespace vk {

	struct instance;

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::application_info>::less_or_equals<1u>,
			types::count_of_ranges_of_value_type<vk::layer_name>::less_or_equals<1u>,
			types::count_of_ranges_of_value_type<vk::extension_name>::less_or_equals<1u>
		>::for_types_of<Args...>
	)
	elements::one_of<vk::instance, vk::result>
	try_create_instance(Args... args) {
		instance_create_info ici{};

		if constexpr(types::count_of_ranges_of_value_type<vk::extension_name>::equals<1u>::for_types_of<Args...>) {
			auto& range = elements::range_of_value_type<vk::extension_name>::for_elements_of(args...);
			ici.enabled_extension_count = (uint32) range.size();
			ici.enabled_extension_names = range.data();
		}

		if constexpr(types::count_of_ranges_of_value_type<vk::layer_name>::equals<1u>::for_types_of<Args...>) {
			auto& range = elements::range_of_value_type<vk::layer_name>::for_elements_of(args...);
			ici.enabled_layer_count = (uint32) range.size();
			ici.enabled_layer_names = range.data();
		}

		vk::instance* instance_ptr;

		vk::result result{
			(uint32) vkCreateInstance(
				(VkInstanceCreateInfo*) &ici,
				nullptr,
				(VkInstance*) instance_ptr
			)
		};

		if(result.success()) {
			return move(*instance_ptr);
		}

		return result;
	}

}