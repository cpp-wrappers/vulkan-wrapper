#pragma once

#include "handle.hpp"
#include "create_info.hpp"
#include "queue_create_info.hpp"

#include <core/range/of_value_type_same_as.hpp>
#include <core/meta/type/disjuncted_predicates.hpp>
#include <core/meta/type/negated_predicate.hpp>
#include <core/meta/elements/pass_satisfying_type_predicate.hpp>
#include <core/meta/type/conjuncted_predicates.hpp>

#include "vk/physical_device/handle.hpp"
#include "vk/physical_device/features_2.hpp"
#include "vk/create_or_allocate.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::device> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::are_contain_decayed<handle<vk::physical_device>>,
			types::are_may_contain_range_of<vk::queue_create_info>,
			types::are_may_contain_range_of<vk::extension_name>,
			types::are_may_contain_one_decayed<vk::physical_device_features>,
			types::are_may_contain_decayed_satisfying_predicate<vk::is_physical_device_features>
		>::for_types<Args...>
		vk::expected<handle<vk::device>>
		operator () (Args&&... args) const {
			vk::device_create_info ci{};

			auto& physical_device = elements::decayed<handle<vk::physical_device>>(args...);

			if constexpr(types::are_contain_range_of<vk::queue_create_info>::for_types<Args...>) {
				const auto& queue_create_infos = elements::range_of<vk::queue_create_info>(args...);
				ci.queue_create_info_count = (uint32) queue_create_infos.size();
				ci.queue_create_infos = queue_create_infos.data();
			}

			if constexpr(types::are_contain_range_of<vk::extension_name>::for_types<Args...>) {
				const auto& extensions = elements::range_of<vk::extension_name>(args...);
				ci.enabled_extension_count = (uint32) extensions.size();
				ci.enabled_extension_names = extensions.data();
			}

			constexpr bool contain_features = types::are_contain_decayed<vk::physical_device_features>::for_types<Args...>;
			constexpr bool contain_aditional_features = types::are_contain_decayed_satisfying_predicate<vk::is_physical_device_features>::for_types<Args...>;

			vk::physical_device_features_2 features_2{};

			if constexpr(contain_aditional_features) {

				if constexpr(contain_features) {
					features_2.features = elements::decayed_satisfying_predicate<vk::is_physical_device_features>(args...);
				}

				const void** next = &features_2.next;

				elements::for_each_decayed_satisfying_predicate<vk::is_physical_device_features>(args...)([&](auto& features){
					*next = &features;
					next = &features.next;
				});

				ci.next = &features_2;
			}
			else if constexpr (contain_features) {
				ci.enabled_features = elements::decayed<vk::physical_device_features>(args...);
			}

			handle<vk::device> device;

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
			types::are_contain_one_decayed<handle<vk::physical_device>>,
			types::are_contain_one_decayed<vk::queue_family_index>,
			types::are_contain_one_decayed<vk::queue_priority>,
			types::are_may_contain_decayed<vk::extension_name>,
			types::are_may_contain_one_decayed<vk::physical_device_features>,
			types::are_may_contain_decayed_satisfying_predicate<vk::is_physical_device_features>
		>::for_types<Args...>
		vk::expected<handle<vk::device>>
		operator () (Args&&... args) const {
			nuint extensions_count = types::count_of_decayed<vk::extension_name>::for_types<Args...>;
			vk::extension_name extension_names[extensions_count];
			nuint extensions = 0;

			elements::for_each_decayed<vk::extension_name>(args...)(
				[&](vk::extension_name name) { extension_names[extensions++] = name; }
			);

			vk::queue_family_index family_index = elements::decayed<vk::queue_family_index>(args...);
			vk::queue_priority priority = elements::decayed<vk::queue_priority>(args...);

			vk::queue_priorities priorities { &priority };

			vk::queue_create_info ci { family_index, priorities, vk::queue_count{ 1 } };

			return elements::pass_not_satisfying_type_predicate<
				type::disjuncted_predicates<
					type::is_decayed<vk::extension_name>,
					type::is_decayed<vk::queue_family_index>,
					type::is_decayed<vk::queue_priority>
				>
			>(
				array{ ci },
				span{ extension_names, extensions_count },
				args...
			)(
				[]<typename... NewArgs>(NewArgs&&... args) {
					return vk::create_t<vk::device>{}(forward<NewArgs>(args)...);
				}
			);
		}

	};

} // vk