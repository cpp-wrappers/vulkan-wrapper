#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/memory_size.hpp"
#include "../__internal/memory_offset.hpp"
#include "../__instance/handle.hpp"
#include "../__buffer/handle.hpp"
#include "../__device/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct cmd_update_buffer_function : vk::function<void(*)(
		handle<vk::command_buffer>::underlying_type command_buffer,
		handle<vk::buffer>::underlying_type dst_buffer,
		uint64 offset,
		uint64 size,
		const void* data
	)> {
		static constexpr auto name = "vkCmdUpdateBuffer";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::command_buffer>>.decayed == 1,
		is_same_as<handle<vk::buffer>>.decayed == 1,
		is_same_as<vk::memory_offset>.decayed <= 1,
		is_same_as<vk::memory_size>.decayed == 1,
		is_same_as<void*>.decayed == 1
	>
	void cmd_update_buffer(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();
		
		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::command_buffer> command_buffer = a.template
			get<is_same_as<handle<vk::command_buffer>>.decayed>();

		handle<vk::buffer> buffer = a.template
			get<is_same_as<handle<vk::buffer>>.decayed>();

		vk::memory_size size = a.template
			get<is_same_as<vk::memory_size>.decayed>();

		void* data = a.template
			get<is_same_as<void*>.decayed>();

		vk::memory_offset offset{};

		if constexpr(
			(is_same_as<vk::memory_offset>.decayed > 0).for_types<Args...>()
		) {
			offset = a.template
				get<is_same_as<vk::memory_offset>.decayed>();
		}

		vk::get_device_function<vk::cmd_update_buffer_function>(
			instance, device
		)(
			command_buffer.underlying(),
			buffer.underlying(),
			offset,
			size,
			data
		);
	}

}