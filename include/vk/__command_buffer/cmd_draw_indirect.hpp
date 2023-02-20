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
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::command_buffer>> == 1,
		count_of_decayed_same_as<handle<vk::buffer>> == 1,
		count_of_decayed_same_as<vk::memory_offset> <= 1,
		count_of_decayed_same_as<vk::draw_count> == 1,
		count_of_decayed_same_as<vk::stride> == 1
	>
	void cmd_draw_indirect(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::command_buffer> command_buffer = a.template
			get_decayed_same_as<handle<vk::command_buffer>>();

		handle<vk::buffer> buffer = a.template
			get_decayed_same_as<handle<vk::buffer>>();

		vk::memory_offset offset{};

		if constexpr(types<Args...>::template
			count_of_decayed_same_as<vk::memory_offset> > 0
		) {
			offset = a.template get_decayed_same_as<vk::memory_offset>();
		}

		vk::draw_count draw_count = a.template
			get_decayed_same_as<vk::draw_count>();

		vk::stride stride = a.template get_decayed_same_as<vk::stride>();

		vk::get_device_function<vk::cmd_draw_indirect_function>(
			instance, device
		)(
			command_buffer.underlying(),
			buffer.underlying(),
			offset,
			draw_count,
			stride
		);
	}

}