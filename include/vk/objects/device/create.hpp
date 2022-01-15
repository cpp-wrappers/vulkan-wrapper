#pragma once

#include <core/elements/pass_satisfying_type_predicate.hpp>
#include <core/type/disjuncted_predicates.hpp>
#include <core/type/negated_predicate.hpp>
#include <core/type/remove_const.hpp>
#include <core/types/are_contain_range_of_value_type.hpp>
#include <core/types/are_contain_one_type.hpp>

#include "handle.hpp"
#include "create_info.hpp"
#include "queue_create_info.hpp"
#include "../physical_device/handle.hpp"
#include "../../object/create_or_allocate.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::device> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::physical_device>,
			types::count_of_ranges_of_value_type<vk::queue_create_info>::less_or_equals<1>,
			types::count_of_ranges_of_value_type<vk::extension_name>::less_or_equals<1>
		>::for_types_of<Args...>
		vk::expected<vk::handle<vk::device>>
		operator () (Args&&... args) const {
			vk::device_create_info ci{};

			auto& physical_device = elements::vk::possibly_guarded_handle_of<vk::physical_device>::for_elements_of(args...);

			if constexpr(types::are_contain_range_of_value_type<vk::queue_create_info>::for_types_of<Args...>) {
				const auto& queue_create_infos = elements::range_of_value_type<vk::queue_create_info>::for_elements_of(args...);
				ci.queue_create_info_count = (uint32) queue_create_infos.size();
				ci.queue_create_infos = queue_create_infos.data();
			}
			if constexpr(types::are_contain_range_of_value_type<vk::extension_name>::for_types_of<Args...>) {
				const auto& extensions = elements::range_of_value_type<vk::extension_name>::for_elements_of(args...);
				ci.enabled_extension_count = (uint32) extensions.size();
				ci.enabled_extension_names = extensions.data();
			}

			vk::handle<vk::device> device;

			vk::result result {
				(int32) vkCreateDevice(
					(VkPhysicalDevice) physical_device.value,
					(VkDeviceCreateInfo*) &ci,
					(VkAllocationCallbacks*) nullptr,
					(VkDevice*) &device
				)
			};
			if(result.error()) return result;
			return device;
		}

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::are_contain_one_type<vk::queue_family_index>::decay,
			types::count_of_ranges_of_value_type<vk::queue_priority>::equals<1>
		>::for_types_of<Args...>
		vk::expected<vk::handle<vk::device>>
		operator () (Args&&... args) const {
			auto& priorities = elements::range_of_value_type<vk::queue_priority>::for_elements_of(args...);
			auto index = elements::of_type<vk::queue_family_index>::ignore_const::ignore_reference::for_elements_of(args...);

			return elements::pass_satisfying_type_predicate<
				type::negated_predicate<
					type::disjuncted_predicates<
						type::is_range_of_value_type<vk::queue_priority>,
						type::is_same_as<vk::queue_family_index>::ignore_const::ignore_reference
					>
				>
			>::to_function{
				[&, this]<typename... Others>(Others&&... others) {
					return this->operator () (
						array {
							vk::queue_create_info {
								index, vk::queue_count{ (uint32) priorities.size() }, vk::queue_priorities{ priorities.data() }
							}
						},
						forward<Others>(others)...
					);
				}
			}.for_elements_of(forward<Args>(args)...);
		}

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::physical_device>,
			types::count_of_type<vk::queue_family_index>::equals<1>,
			types::count_of_type<vk::queue_priority>::equals<1>,
			types::count_of_type<vk::extension_name>::greater_or_equals<0>
		>::for_types_of<Args...>
		vk::expected<vk::handle<vk::device>>
		operator () (const Args&... args) const {
			nuint extensions_count = types::count_of_type<vk::extension_name>::for_types_of<Args...>;
			vk::extension_name extension_names[extensions_count];
			nuint extension_index = 0;

			elements::for_each_of_type<vk::extension_name>::ignore_const::ignore_reference::function {
				[&](vk::extension_name name) { extension_names[extension_index++] = name; }
			}.for_elements_of(args...);

			vk::queue_family_index family_index = elements::of_type<const vk::queue_family_index&>::for_elements_of(args...);
			auto physical_device = elements::vk::possibly_guarded_handle_of<vk::physical_device>::for_elements_of(args...);
			vk::queue_priority priority = elements::of_type<const vk::queue_priority&>::for_elements_of(args...);

			vk::queue_priorities priorities { &priority };

			vk::queue_create_info ci { family_index, priorities, vk::queue_count{ 1 } };

			return this->operator() (physical_device, array{ ci }, span{ extension_names, extensions_count });
		}

	};

} // vk