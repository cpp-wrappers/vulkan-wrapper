#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"
#include "../__pipeline_layout/handle.hpp"
#include "../__pipeline/push_constant_range.hpp"
#include "../__shader_module/stage.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct cmd_push_constants_function : vk::function<void(*)(
		handle<vk::command_buffer>::underlying_type command_buffer,
		handle<vk::pipeline_layout>::underlying_type layout,
		int /*vk::shader_stages*/ stages,
		uint32 offset,
		uint32 size,
		const void* values
	)> {
		static constexpr auto name = "vkCmdPushConstants";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::command_buffer>>.decayed == 1,
		is_same_as<handle<vk::pipeline_layout>>.decayed == 1,
		is_same_as<vk::push_constant_range>.decayed == 1,
		is_same_as<void*>.decayed == 1
	>
	void cmd_push_constants(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::command_buffer> command_buffer = a.template
			get<is_same_as<handle<vk::command_buffer>>.decayed>();

		handle<vk::pipeline_layout> pipeline_layout = a.template
			get<is_same_as<handle<vk::pipeline_layout>>.decayed>();

		vk::push_constant_range range = a.template
			get<is_same_as<vk::push_constant_range>.decayed>();

		void* values = a.template
			get<is_same_as<void*>.decayed>();

		vk::get_device_function<vk::cmd_push_constants_function>(
			instance, device
		)(
			command_buffer.underlying(),
			pipeline_layout.underlying(),
			range.stages,
			(uint32) range.offset,
			(uint32) range.size,
			values
		);
	}

} // vk