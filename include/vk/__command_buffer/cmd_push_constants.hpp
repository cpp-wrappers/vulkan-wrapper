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
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::command_buffer>> == 1,
		count_of_decayed_same_as<handle<vk::pipeline_layout>> == 1,
		count_of_decayed_same_as<vk::push_constant_range> == 1,
		count_of_decayed_same_as<void*> == 1
	>
	void cmd_push_constants(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::command_buffer> command_buffer = a.template
			get_decayed_same_as<handle<vk::command_buffer>>();

		handle<vk::pipeline_layout> pipeline_layout = a.template
			get_decayed_same_as<handle<vk::pipeline_layout>>();

		vk::push_constant_range range = a.template
			get_decayed_same_as<vk::push_constant_range>();

		void* values = a.template
			get_decayed_same_as<void*>();

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