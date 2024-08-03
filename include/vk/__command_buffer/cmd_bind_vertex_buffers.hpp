#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/first_binding.hpp"
#include "../__internal/binding.hpp"
#include "../__internal/memory_offset.hpp"
#include "../__buffer/handle.hpp"
#include "../__device/handle.hpp"
#include "../__instance/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct cmd_bind_vertex_buffers_function : vk::function<void(*)(
		handle<vk::command_buffer>::underlying_type command_buffer,
		uint32 first_binding,
		uint32 binding_count,
		const handle<vk::buffer>::underlying_type* buffers,
		const vk::memory_offset* offsets
	)> {
		static constexpr auto name = "vkCmdBindVertexBuffers";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::command_buffer>>.decayed == 1,
		is_same_as<vk::first_binding>.decayed <= 1,
		is_range_of<is_same_as<handle<vk::buffer>>.decayed> == 1,
		is_range_of<is_same_as<vk::memory_offset>.decayed> == 1
	>
	void cmd_bind_vertex_buffers(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::command_buffer> command_buffer = a.template
			get<is_same_as<handle<vk::command_buffer>>.decayed>();
		
		vk::first_binding first_binding{ 0 };

		if constexpr (
			(is_same_as<vk::first_binding>.decayed > 0)
			.for_types<Args...>()
		) {
			first_binding = a.template
				get<is_same_as<vk::first_binding>.decayed>();
		}

		auto& buffers = a.template
				get<is_range_of<is_same_as<handle<vk::buffer>>.decayed>>();
		auto& offsets = a.template
				get<is_range_of<is_same_as<vk::memory_offset>.decayed>>();

		vk::get_device_function<vk::cmd_bind_vertex_buffers_function>(
			instance, device
		)(
			command_buffer.underlying(),
			(uint32) first_binding,
			(uint32) buffers.size(),
			(const handle<vk::buffer>::underlying_type*) buffers.iterator(),
			offsets.iterator()
		);
	}

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>> == 1,
		is_same_as<handle<vk::device>> == 1,
		is_same_as<handle<vk::command_buffer>> == 1,
		is_same_as<vk::binding> == 1,
		is_same_as<handle<vk::buffer>> == 1,
		is_same_as<vk::memory_offset> <= 1
	>
	void cmd_bind_vertex_buffer(Args... args) {
		tuple<Args...> a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>>();

		handle<vk::command_buffer> command_buffer = a.template
			get<is_same_as<handle<vk::command_buffer>>>();
		
		vk::binding binding = a.template
			get<is_same_as<vk::binding>>();

		handle<vk::buffer> buffer = a.template
			get<is_same_as<handle<vk::buffer>>>();

		vk::memory_offset offset = a.template
			get_or<is_same_as<vk::memory_offset>>(
				[]{ return vk::memory_offset{0}; }
			);

		vk::cmd_bind_vertex_buffers(
			instance, device, command_buffer,
			vk::first_binding{ (uint32) binding },
			array{ buffer }, array{ offset }
		);
	}

} // vk