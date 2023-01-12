#pragma once

#include "./handle.hpp"
#include "./create_info.hpp"
#include "../__internal/function.hpp"
#include "../__internal/result.hpp"
#include "../__physical_device/handle.hpp"
#include "../__physical_device/features_2.hpp"

#include <tuple.hpp>

extern "C" VK_ATTR int32 VK_CALL vkCreateDevice(
	vk::physical_device*          physical_device,
	const vk::device_create_info* create_info,
	const void*                   allocator,
	vk::device**                  device
);

namespace vk {

	template<nuint Order, typename... Args>
	requires (Order == 0) &&
	types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::physical_device>> == 1,
		count_of_range_of<vk::queue_create_info> <= 1,
		count_of_range_of<vk::extension_name> <= 1,
		count_of_decayed_same_as<vk::physical_device_features>,
		count_of_satisfying_predicate<vk::is_physical_device_features> >= 0
	>
	vk::expected<handle<vk::device>>
	try_create_device(Args&&... args) {
		vk::device_create_info ci{};

		auto& physical_device = tuple{ args... }.template
			get_decayed_same_as<handle<vk::physical_device>>();

		if constexpr (types<Args...>::template
			count_of_range_of<vk::queue_create_info> > 0
		) {
			const auto& queue_create_infos = tuple{ args... }.template
				get_range_of<vk::queue_create_info>();

			ci.queue_create_info_count = (uint32) queue_create_infos.size();
			ci.queue_create_infos = queue_create_infos.data();
		}

		if constexpr (types<Args...>::template
			count_of_range_of<vk::extension_name> > 0
		) {
			const auto& extensions = tuple{ args... }.template
				get_range_of<vk::extension_name>();

			ci.enabled_extension_count = (uint32) extensions.size();
			ci.enabled_extension_names = extensions.data();
		}

		constexpr bool contain_features = types<Args...>::template
			count_of_decayed_same_as<vk::physical_device_features> > 0;

		constexpr bool contain_aditional_features = types<Args...>::template
			count_of_satisfying_predicate<vk::is_physical_device_features> > 0;

		vk::physical_device_features_2 features_2{};

		if constexpr(contain_aditional_features) {
			if constexpr(contain_features) {
				features_2.features = tuple{ args... }.template
					get_satisfying_predicate<vk::is_physical_device_features>();
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