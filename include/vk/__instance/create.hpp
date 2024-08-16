#pragma once

#include "./handle.hpp"
#include "./create_info.hpp"

#include "../__internal/function.hpp"
#include "../__internal/result.hpp"
#include "../__internal/unexpected_handler.hpp"

#include <body.hpp>
#include <types.hpp>

namespace vk {

	struct create_instance_function : function<int32(VK_PTR *)(
		const vk::instance_create_info* create_info,
		const void* allocator,
		handle<vk::instance>::underlying_type* instance
	)> {
		static constexpr auto name = "vkCreateInstance";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<vk::application_info>.decayed >= 0,
		is_range_of<is_same_as<vk::layer_name>.decayed> >= 0,
		is_range_of<is_same_as<vk::extension_name>.decayed> >= 0
	>
	vk::expected<handle<vk::instance>> try_create_instance(Args&&... args) {
		instance_create_info ici{};

		if constexpr(
			(is_same_as<vk::application_info>.decayed > 0).for_types<Args...>()
		) {
			ici.application_info = & tuple{ args... }.template
				get<is_same_as<vk::application_info>.decayed>();
		}

		if constexpr(types<Args...>::template
			count_of<is_range_of<
				is_same_as<vk::extension_name>.decayed
			>> > 0
		) {
			auto& range = tuple{ args... }.template
				get<is_range_of<is_same_as<vk::extension_name>.decayed>>();
			ici.enabled_extension_count = (uint32) range.size();
			ici.enabled_extension_names = range.iterator();
		}

		if constexpr(types<Args...>::template
			count_of<is_range_of<
				is_same_as<vk::layer_name>.decayed
			>> > 0
		) {
			auto& range = tuple{ args... }.template
				get<is_range_of<is_same_as<vk::layer_name>.decayed>>();
			ici.enabled_layer_count = (uint32) range.size();
			ici.enabled_layer_names = range.iterator();
		}

		handle<vk::instance> instance{};

		vk::result result {
			vk::get_global_function<vk::create_instance_function>()(
				&ici,
				nullptr,
				&instance.underlying()
			)
		};

		if (result.error()) {
			return result;
		}

		return instance;
	};

	template<typename... Args>
	handle<vk::instance> create_instance(Args&&... args) {
		vk::expected<handle<vk::instance>> result
			= vk::try_create_instance(::forward<Args>(args)...);
		if (result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk