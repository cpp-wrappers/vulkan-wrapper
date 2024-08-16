#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/memory_offset.hpp"
#include "../__internal/stride.hpp"
#include "../__buffer/handle.hpp"
#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	class draw_count {
		uint32 value_;
	public:
		draw_count(uint32 value) : value_{ value } {}
		operator uint32() const { return value_; }
	};

	struct cmd_draw_indirect_function : vk::function<void(*)(
		handle<vk::command_buffer>::underlying_type command_buffer,
		handle<vk::buffer>::underlying_type buffer,
		uint64 /*vk::memory_offset*/ offset,
		uint32 /*vk::draw_count*/ draw_count,
		uint32 /*vk::stride*/ stride
	)> {
		static constexpr auto name = "vkCmdDrawIndirect";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::command_buffer>>.decayed == 1,
		is_same_as<handle<vk::buffer>>.decayed == 1,
		is_same_as<vk::memory_offset>.decayed <= 1,
		is_same_as<vk::draw_count>.decayed == 1,
		is_same_as<vk::stride>.decayed == 1
	>
	void cmd_draw_indirect(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::command_buffer> command_buffer = a.template
			get<is_same_as<handle<vk::command_buffer>>.decayed>();

		handle<vk::buffer> buffer = a.template
			get<is_same_as<handle<vk::buffer>>.decayed>();

		vk::memory_offset offset{};

		if constexpr(
			(is_same_as<vk::memory_offset>.decayed > 0)
			.for_types<Args...>()
		) {
			offset = a.template ge<is_same_as<vk::memory_offset>.decayed>();
		}

		vk::draw_count draw_count = a.template
			get<is_same_as<vk::draw_count>.decayed>();

		vk::stride stride = a.template get<is_same_as<vk::stride>.decayed>();

		vk::get_device_function<vk::cmd_draw_indirect_function>(
			instance, device
		)(
			command_buffer.underlying(),
			buffer.underlying(),
			(uint64) offset,
			draw_count,
			stride
		);
	}

}