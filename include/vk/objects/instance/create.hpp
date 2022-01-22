#pragma once

#include "handle.hpp"
#include "create_info.hpp"
#include "../../object/create_or_allocate.hpp"

#include <core/meta/decayed_same_as.hpp>

namespace vk {

	template<>
	struct vk::create_t<vk::instance> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::are_may_contain_one_decayed_same_as<vk::application_info>,
			types::count_of_ranges_of_value_type<vk::layer_name>::less_or_equals<1>,
			types::count_of_ranges_of_value_type<vk::extension_name>::less_or_equals<1>
		>::for_types<Args...>
		vk::expected<vk::handle<vk::instance>>
		operator () (Args&&... args) const {
			instance_create_info ici{};

			if constexpr(types::are_contain_decayed_same_as<vk::application_info>::for_types<Args...>) {
				ici.application_info =
					& elements::decayed_same_as<
						vk::application_info
					>(args...);
			}

			if constexpr(types::count_of_ranges_of_value_type<vk::extension_name>::equals<1>::for_types<Args...>) {
				auto& range = elements::range_of_value_type<vk::extension_name>(args...);
				ici.enabled_extension_count = (uint32) range.size();
				ici.enabled_extension_names = range.data();
			}

			if constexpr(types::count_of_ranges_of_value_type<vk::layer_name>::equals<1>::for_types<Args...>) {
				auto& range = elements::range_of_value_type<vk::layer_name>(args...);
				ici.enabled_layer_count = (uint32) range.size();
				ici.enabled_layer_names = range.data();
			}

			vk::handle<vk::instance> instance;

			vk::result result {
				(int32) vkCreateInstance(
					(VkInstanceCreateInfo*) &ici,
					(VkAllocationCallbacks*) nullptr,
					(VkInstance*) &instance
				)
			};

			if(result.error()) return result;

			return instance;
		}

	};

} // vk