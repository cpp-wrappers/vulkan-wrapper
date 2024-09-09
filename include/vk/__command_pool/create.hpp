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
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		(
			is_same_as<vk::command_pool_create_flags>.decayed <= 1
			|| is_same_as<vk::command_pool_create_flag>.decayed >= 0
		),
		is_same_as<vk::queue_family_index>.decayed == 1
	>
	vk::expected<handle<vk::command_pool>>
	try_create_command_pool(Args&&... args) {
		tuple a{ args...};

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		vk::command_pool_create_info ci{};

		ci.queue_family_index = a.template
			get<is_same_as<vk::queue_family_index>.decayed>();

		if constexpr (
			(is_same_as<vk::command_pool_create_flags>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.flags = a.template
				get<is_same_as<vk::command_pool_create_flags>.decayed>();
		}

		a.template pass<is_same_as<vk::command_pool_create_flag>.decayed>(
			[&](auto... flag) { (ci.flags.set(flag), ...); }
		);

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

		if (result.error()) return result;

		return command_pool;
	}

	template<typename... Args>
	handle<vk::command_pool> create_command_pool(Args&&... args) {
		expected<handle<vk::command_pool>> result
			= vk::try_create_command_pool(forward<Args>(args)...);
		if (result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk