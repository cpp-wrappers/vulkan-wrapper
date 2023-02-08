#pragma once

#include "./handle.hpp"
#include "./create_info.hpp"
#include "../__internal/function.hpp"
#include "../__internal/result.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__physical_device/handle.hpp"
#include "../__physical_device/features_2.hpp"

#include <tuple.hpp>
#include <types.hpp>
#include <body.hpp>

namespace vk {

	struct create_device_function : vk::function<int32(*)(
		vk::physical_device*          physical_device,
		const vk::device_create_info* create_info,
		const void*                   allocator,
		vk::device**                  device
	)> {
		static constexpr auto name = "vkCreateDevice";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::physical_device>> == 1,
		count_of_range_of_decayed<vk::queue_create_info> <= 1,
		count_of_range_of_decayed<vk::extension_name> <= 1,
		count_of_decayed_same_as<vk::physical_device_features> >= 0,
		count_of_satisfying_predicate<vk::is_physical_device_features> >= 0
	>
	vk::expected<handle<vk::device>>
	try_create_device(Args&&... args) {
		vk::device_create_info ci{};

		handle<vk::instance> instance = tuple { args... }.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::physical_device> physical_device = tuple { args... }.template
			get_decayed_same_as<handle<vk::physical_device>>();

		if constexpr (types<Args...>::template
			count_of_range_of_decayed<vk::queue_create_info> > 0
		) {
			const auto& queue_create_infos = tuple { args... }.template
				get_range_of_decayed<vk::queue_create_info>();

			ci.queue_create_info_count = (uint32) queue_create_infos.size();
			ci.queue_create_infos = queue_create_infos.iterator();
		}

		if constexpr (types<Args...>::template
			count_of_range_of_decayed<vk::extension_name> > 0
		) {
			const auto& extensions = tuple { args... }.template
				get_range_of_decayed<vk::extension_name>();

			ci.enabled_extension_count = (uint32) extensions.size();
			ci.enabled_extension_names = extensions.iterator();
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

			tuple{ args... }.template for_each(
				[&]<typename Type>(Type& possibly_features) {
					if constexpr(
						vk::is_physical_device_features.for_type<Type>()
					) {
						*next = &possibly_features;
						next = &possibly_features.next;
					}
				}
			);

			ci.next = &features_2;
		}
		else if constexpr (contain_features) {
			ci.enabled_features = & tuple{ args... }.template
				get_decayed<vk::physical_device_features>();
		}

		handle<vk::device> device;

		vk::result result {
			vk::get_instance_function<vk::create_device_function>(instance)(
				physical_device.underlying(),
				&ci,
				nullptr,
				&device.underlying()
			)
		};

		if(result.error()) return result;

		return device;
	}

	template<typename... Args>
	handle<vk::device> create_device(Args&&... args) {
		vk::expected<handle<vk::device>> result
			= try_create_device(forward<Args>(args)...);
		
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk