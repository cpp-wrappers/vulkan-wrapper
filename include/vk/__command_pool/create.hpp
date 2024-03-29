#pragma once

#include "./handle.hpp"
#include "./create_info.hpp"
#include "../__device/handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__internal/result.hpp"

#include <handle.hpp>
#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct create_command_pool_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		const vk::command_pool_create_info* create_info,
		const void* allocator,
		handle<vk::command_pool>::underlying_type* command_pool
	)> {
		static constexpr auto name = "vkCreateCommandPool";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<vk::command_pool_create_flags> <= 1,
		count_of_decayed_same_as<vk::queue_family_index> == 1
	>
	vk::expected<handle<vk::command_pool>>
	try_create_command_pool(Args&&... args) {
		handle<vk::instance> instance = tuple{ args... }.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = tuple{ args... }.template
			get_decayed_same_as<handle<vk::device>>();

		vk::command_pool_create_info ci{};

		ci.queue_family_index = tuple{ args... }.template
			get_decayed_same_as<vk::queue_family_index>();

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::command_pool_create_flags> > 0
		) {
			ci.flags = tuple{ args... }.template
				get_decayed_same_as<vk::command_pool_create_flags>();
		}

		handle<vk::command_pool> command_pool;

		vk::result result {
			vk::get_device_function<create_command_pool_function>(
				instance,
				device
			)(
				device.underlying(),
				&ci,
				nullptr,
				&command_pool.underlying()
			)
		};

		if(result.error()) return result;

		return command_pool;
	}

	template<typename... Args>
	handle<vk::command_pool> create_command_pool(Args&&... args) {
		expected<handle<vk::command_pool>> result
			= vk::try_create_command_pool(forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk