#pragma once

#include <core/elements/pass_satisfying_type_predicate.hpp>
#include <core/type/disjuncted_predicates.hpp>
#include <core/type/negated_predicate.hpp>
#include <core/type/remove_const.hpp>

#include "handle.hpp"
#include "create_info.hpp"
#include "queue_create_info.hpp"
#include "../physical_device/handle.hpp"

namespace vk {

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::handle<vk::physical_device>>::equals<1>,
			types::count_of_ranges_of_value_type<vk::queue_create_info>::less_or_equals<1>,
			types::count_of_ranges_of_value_type<vk::extension_name>::less_or_equals<1>
		>::for_types_of<Args...>
	)
	elements::one_of<vk::result, vk::handle<vk::device>>
	try_create_device(const Args&... args) {
		vk::device_create_info ci{};

		auto& physical_device = elements::of_type<const vk::handle<vk::physical_device>&>::for_elements_of(args...);

		if constexpr(types::count_of_ranges_of_value_type<vk::queue_create_info>::equals<1>::for_types_of<Args...>) {
			const auto& queue_create_infos = elements::range_of_value_type<vk::queue_create_info>::for_elements_of(args...);
			ci.queue_create_info_count = (uint32) queue_create_infos.size();
			ci.queue_create_infos = queue_create_infos.data();
		}
		if constexpr(types::count_of_ranges_of_value_type<vk::extension_name>::equals<1>::for_types_of<Args...>) {
			const auto& extensions = elements::range_of_value_type<vk::extension_name>::for_elements_of(args...);
			ci.enabled_extension_count = (uint32) extensions.size();
			ci.enabled_extension_names = extensions.data();
		}

		VkDevice device;

		vk::result result {
			(int32) vkCreateDevice(
				(VkPhysicalDevice) physical_device.value,
				(VkDeviceCreateInfo*) &ci,
				nullptr,
				(VkDevice*) &device
			)
		};
		if(result.success()) return device;
		return result;
	}

	template<typename... Args>
	requires(
		types::count_of_type<vk::queue_family_index>::for_types_of<Args...> == 1 &&
		types::count_of_ranges_of_value_type<vk::queue_priority>::for_types_of<Args...> == 1
	)
	elements::one_of<vk::result, vk::handle<vk::device>>
	try_create_device(const Args&... args) {
		auto& priorities = elements::range_of_value_type<vk::queue_priority>::for_elements_of(args...);
		auto index = elements::of_type<const vk::queue_family_index&>::for_elements_of(args...);

		return elements::pass_satisfying_type_predicate<
			type::negated_predicate<
				type::disjuncted_predicates<
					type::is_range_of_value_type<vk::queue_priority>,
					type::is_same_as<vk::queue_family_index>::ignore_const::ignore_reference
				>
			>
		>::to_function{
			[&](auto&... others) {
				return try_create_device(
					array {
						vk::queue_create_info {
							index, vk::queue_count{ (uint32) priorities.size() }, vk::queue_priorities{ priorities.data() }
						}
					},
					others...
				);
			}
		}.for_elements_of(args...);
	}

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::physical_device>::equals<1>,
			types::count_of_type<vk::queue_family_index>::equals<1>,
			types::count_of_type<vk::queue_priority>::equals<1>,
			types::count_of_type<vk::extension_name>::greater_or_equals<0>
		>::for_types_of<Args...>
	)
	elements::one_of<vk::result, vk::handle<vk::device>>
	try_create_device(const Args&... args) {
		nuint extensions_count = types::count_of_type<vk::extension_name>::for_types_of<Args...>;
		vk::extension_name extension_names[extensions_count];
		nuint extension_index = 0;

		elements::for_each_of_type<const vk::extension_name&>([&](vk::extension_name name) {
			extension_names[extension_index++] = name;
		}, args...);

		vk::queue_family_index family_index = elements::of_type<const vk::queue_family_index&>::for_elements_of(args...);
		vk::handle<vk::physical_device>& physical_device = elements::of_type<const vk::handle<vk::physical_device>&>::for_elements_of(args...);
		vk::queue_priority priority = elements::of_type<const vk::queue_priority&>::for_elements_of(args...);

		vk::queue_priorities priorities { &priority };

		vk::queue_create_info ci { family_index, priorities, vk::queue_count{ 1 } };

		return vk::try_create_device(physical_device, array{ ci }, span{ extension_names, extensions_count });
	}

	template<typename... Args>
	vk::handle<vk::device> create_device(const Args&... args) {
		auto result = try_create_device(args...);
		if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
		return result.template get<vk::handle<vk::device>>();
	}
} // vk