#pragma once

#include "./handle.hpp"
#include "./begin_info.hpp"
#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/result.hpp"
#include "../__internal/unexpected_handler.hpp"

#include <tuple.hpp>

namespace vk {

	struct begin_command_buffer_function : vk::function<int32(*)(
		handle<vk::command_buffer>::underlying_type command_buffer,
		const vk::command_buffer_begin_info* begin_info
	)> {
		static constexpr auto name = "vkBeginCommandBuffer";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::command_buffer>>.decayed == 1,
		is_same_as<vk::command_buffer_usages>.decayed <= 1,
		is_same_as<vk::command_buffer_inheritance_info>.decayed <= 1
	>
	vk::result try_begin_command_buffer(Args&&... args) {
		tuple a { args... };
		vk::command_buffer_begin_info bi {};

		if constexpr (
			(is_same_as<vk::command_buffer_usages>.decayed > 0)
			.for_types<Args...>()
		) {
			bi.usages = a.template
				get<is_same_as<vk::command_buffer_usages>.decayed>();
		}

		if constexpr (
			(is_same_as<vk::command_buffer_inheritance_info>.decayed > 0)
			.for_types<Args...>()
		) {
			bi.inheritance_info = a.template
				get<is_same_as<vk::command_buffer_inheritance_info>.decayed>();
		}

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::command_buffer> command_buffer = a.template
			get<is_same_as<handle<vk::command_buffer>>.decayed>();

		return {
			vk::get_device_function<vk::begin_command_buffer_function>(
				instance, device
			)(
				command_buffer.underlying(), &bi
			)
		};
	}

	template<typename... Args>
	void begin_command_buffer(Args&&... args) {
		vk::result result {
			vk::try_begin_command_buffer(forward<Args>(args)...)
		};

		if (result.error()) vk::unexpected_handler(result);
	}

} // vk