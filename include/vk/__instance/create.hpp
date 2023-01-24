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
		count_of_decayed_same_as<vk::application_info> >= 0,
		count_of_range_of_decayed<vk::layer_name> >= 0,
		count_of_range_of_decayed<vk::extension_name> >= 0
	>
	vk::expected<handle<vk::instance>> try_create_instance(Args&&... args) {
		instance_create_info ici{};

		if constexpr(types<Args...>::template
			count_of_decayed_same_as<vk::application_info> > 0
		) {
			ici.application_info = & tuple{ args... }.template
				get_decayed_same_as<vk::application_info>();
		}

		if constexpr(types<Args...>::template
			count_of_range_of_decayed<vk::extension_name> > 0
		) {
			auto& range = tuple{ args... }.template
				get_range_of_decayed<vk::extension_name>();
			ici.enabled_extension_count = (uint32) range.size();
			ici.enabled_extension_names = range.iterator();
		}

		if constexpr(types<Args...>::template
			count_of_range_of_decayed<vk::layer_name> > 0
		) {
			auto& range = tuple{ args... }.template
				get_range_of_decayed<vk::layer_name>();
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

		if(result.error()) {
			return result;
		}

		return instance;
	};

	template<typename... Args>
	handle<vk::instance> create_instance(Args&&... args) {
		vk::expected<handle<vk::instance>> result
			= try_create_instance(forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk