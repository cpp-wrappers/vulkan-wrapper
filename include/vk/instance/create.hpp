#pragma once

#include "handle.hpp"
#include "create_info.hpp"
#include "../shared/create.hpp"

namespace vk {

	template<>
	struct vk::try_create_t<vk::instance> {

		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::count_of_type<vk::application_info>::less_or_equals<1>::ignore_const::ignore_reference,
				types::count_of_ranges_of_value_type<vk::layer_name>::less_or_equals<1>,
				types::count_of_ranges_of_value_type<vk::extension_name>::less_or_equals<1>
			>::for_types_of<Args...>
		)
		elements::one_of<vk::result, vk::handle<vk::instance>>
		operator () (Args&&... args) const {
			instance_create_info ici{};

			if constexpr(types::are_contain_type<vk::application_info>::for_types_of<Args...>) {
				ici.application_info =
					& elements::of_type<
						vk::application_info
					>::ignore_const::ignore_reference::for_elements_of(args...);
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

			if(result.success()) return vk::handle<vk::instance>{ instance };

			return result;
		}

	};
}