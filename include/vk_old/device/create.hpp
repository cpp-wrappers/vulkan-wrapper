#pragma once

#include "handle.hpp"
#include "create_info.hpp"
#include "queue_create_info.hpp"

#include "../physical_device/handle.hpp"
#include "../physical_device/features_2.hpp"
#include "../create_or_allocate.hpp"

#include <core/range_of_value_type_same_as.hpp>
#include <core/meta/type/disjuncted_predicates.hpp>
#include <core/meta/type/negated_predicate.hpp>
#include <core/meta/elements/pass_satisfying_type_predicate.hpp>
#include <core/meta/type/conjuncted_predicates.hpp>

extern "C" VK_ATTR int32 VK_CALL vkCreateDevice(
	handle<vk::physical_device>   physical_device,
	const vk::device_create_info* create_info,
	const void*                   allocator,
	handle<vk::device>*           device
);

namespace vk {

	template<>
	struct vk::create_t<vk::device> {

		template<nuint Order, typename... Args>
		requires (Order == 0) && types::are_exclusively_satisfying_predicates<
			types::are_contain_decayed<handle<vk::physical_device>>,
			types::are_may_contain_range_of<vk::queue_create_info>,
			types::are_may_contain_range_of<vk::extension>,
			types::are_may_contain_one_decayed<vk::physical_device_features>,
			types::are_may_contain_decayed_satisfying_predicate<
				vk::is_physical_device_features
			>
		>::for_types<Args...>
		vk::expected<handle<vk::device>>
		operator () (Args&&... args) const {
			vk::device_create_info ci{};

			auto& physical_device = elements::decayed<
				handle<vk::physical_device>
			>(args...);

			if constexpr (
				types::are_contain_range_of<
					vk::queue_create_info
				>::for_types<Args...>
			) {
				const auto& queue_create_infos = elements::range_of<
					vk::queue_create_info
				>(args...);

				ci.queue_create_info_count = (uint32) queue_create_infos.size();
				ci.queue_create_infos = queue_create_infos.data();
			}

			if constexpr (
				types::are_contain_range_of<
					vk::extension
				>::for_types<Args...>
			) {
				const auto& extensions = elements::range_of<
					vk::extension
				>(args...);

				ci.enabled_extension_count = (uint32) extensions.size();
				ci.enabled_extension_names = extensions.data();
			}

			constexpr bool contain_features {
				types::are_contain_decayed<
					vk::physical_device_features
				>::for_types<Args...>
			};

			constexpr bool contain_aditional_features {
				types::are_contain_decayed_satisfying_predicate<
					vk::is_physical_device_features
				>::for_types<Args...>
			};

			vk::physical_device_features_2 features_2{};

			if constexpr(contain_aditional_features) {

				if constexpr(contain_features) {
					features_2.features = {
						elements::decayed_satisfying_predicate<
							vk::is_physical_device_features
						>(args...)
					};
				}

				const void** next = &features_2.next;

				elements::for_each_decayed_satisfying_predicate<
					vk::is_physical_device_features
				>(args...)([&](auto& features) {
					*next = &features;
					next = &features.next;
				});

				ci.next = &features_2;
			}
			else if constexpr (contain_features) {
				ci.enabled_features = & elements::decayed<
					vk::physical_device_features
				>(args...);
			}

			handle<vk::device> device;

			vk::result result {
				vkCreateDevice(
					physical_device,
					&ci,
					nullptr,
					&device
				)
			};

			if(result.error()) return result;

			return device;
		}

		template<nuint Order, typename... Args>
		auto operator () (Args&&... args) const {
			static_assert(Order > 0);
			return operator () <Order - 1>(forward<Args>(args)...);
		}

		template<nuint Order, typename... Args>
		requires (Order == 1) &&
		types::are_contain_one_decayed<
			vk::queue_family_index
		>::for_types<Args...> &&
		types::are_may_contain_one_decayed<
			vk::queue_priority
		>::for_types<Args...>
		vk::expected<handle<vk::device>>
		operator () (Args&&... args) const {
			vk::queue_family_index family_index {
				elements::decayed<vk::queue_family_index>(args...)
			};

			vk::queue_priority priority { 1.0F };
			if constexpr (
				types::are_contain_decayed<
					vk::queue_priority
				>::for_types<Args...>
			) { priority = elements::decayed<vk::queue_priority>(args...); };

			vk::queue_priorities priorities { &priority };

			vk::queue_create_info ci {
				family_index,
				priorities,
				vk::queue_count{ 1 }
			};

			return elements::pass_not_satisfying_type_predicate<
				type::disjuncted_predicates<
					type::is_decayed<vk::queue_family_index>,
					type::is_decayed<vk::queue_priority>
				>
			>(forward<Args>(args)...)(
				[&]<typename... A>(A&&... a) {
					return operator () <Order - 1>(
						array{ ci },
						forward<A>(a)...
					);
				}
			);
		}

		template<nuint Order, typename... Args>
		requires (Order == 2) &&
		types::are_contain_decayed<vk::extension>::for_types<Args...>
		vk::expected<handle<vk::device>>
		operator () (Args&&... args) const {
			nuint extensions_count = types::count_of_decayed<
				vk::extension>
			::for_types<Args...>;
			vk::extension extension_storage[extensions_count];
			nuint extension_count = 0;
			elements::for_each_decayed<vk::extension>(args...)(
				[&](vk::extension name) {
					extension_storage[extension_count++] = name;
				}
			);
			return elements::pass_not_satisfying_type_predicate<
				type::disjuncted_predicates<type::is_decayed<vk::extension>>
			>(forward<Args>(args)...)(
				[&]<typename... A>(A&&... a) {
					return operator () <Order - 1>(
						span{ extension_storage, extension_count },
						forward<A>(a)...
					);
				}
			);
		}

		template<typename... Args>
		auto operator () (Args&&... args) const {
			return operator () <2, Args...>(forward<Args>(args)...);
		}

	};

} // vk