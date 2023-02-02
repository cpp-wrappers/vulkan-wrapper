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
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::command_buffer>> == 1,
		count_of_decayed_same_as<handle<vk::buffer>> == 1,
		count_of_decayed_same_as<vk::memory_offset> <= 1,
		count_of_decayed_same_as<vk::memory_size> == 1,
		count_of_decayed_same_as<void*> == 1
	>
	void cmd_update_buffer(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();
		
		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::command_buffer> command_buffer = a.template
			get_decayed_same_as<handle<vk::command_buffer>>();

		handle<vk::buffer> buffer = a.template
			get_decayed_same_as<handle<vk::buffer>>();

		vk::memory_size size = a.template
			get_decayed_same_as<vk::memory_size>();

		void* data = a.template get_decayed_same_as<void*>();

		vk::memory_offset offset{};

		if constexpr(types<Args...>::template
			count_of_decayed_same_as<vk::memory_offset> > 0
		) {
			offset = a.template get_decayed_same_as<vk::memory_offset>();
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