#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/first_binding.hpp"
#include "../__internal/memory_offset.hpp"
#include "../__buffer/handle.hpp"
#include "../__device/handle.hpp"
#include "../__instance/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct cmd_bind_vertex_buffers_function : vk::function<void(*)(
		handle<vk::command_buffer>::underlying_type command_buffer,
		vk::first_binding first_binding,
		uint32 binding_count,
		const handle<vk::buffer>::underlying_type* buffers,
		const vk::memory_offset* offsets
	)> {
		static constexpr auto name = "vkCmdBindVertexBuffers";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::command_buffer>> == 1,
		count_of_decayed_same_as<vk::first_binding> <= 1,
		count_of_range_of_decayed<handle<vk::buffer>> == 1,
		count_of_range_of_decayed<vk::memory_offset> == 1
	>
	void cmd_bind_vertex_buffers(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::command_buffer> command_buffer = a.template
			get_decayed_same_as<handle<vk::command_buffer>>();
		
		vk::first_binding first_binding{ 0 };

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::first_binding> > 0
		) {
			first_binding = a.template
				get_decayed_same_as<vk::first_binding>();
		}

		auto& buffers = a.template
				get_range_of_decayed<handle<vk::buffer>>();
		auto& offsets = a.template
				get_range_of_decayed<vk::memory_offset>();

		vk::get_device_function<vk::cmd_bind_vertex_buffers_function>(
			instance, device
		)(
			command_buffer.underlying(),
			first_binding,
			(uint32) buffers.size(),
			(const handle<vk::buffer>::underlying_type*) buffers.iterator(),
			offsets.iterator()
		);
	}

} // vk