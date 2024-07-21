#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"
#include "../__pipeline/bind_point.hpp"
#include "../__pipeline/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct cmd_bind_pipeline_function : vk::function<void(*)(
		handle<vk::command_buffer>::underlying_type command_buffer,
		int /*vk::pipeline_bind_point*/ pipeline_bind_point,
		handle<vk::pipeline>::underlying_type pipeline
	)> {
		static constexpr auto name = "vkCmdBindPipeline";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::command_buffer>>.decayed == 1,
		is_same_as<handle<vk::pipeline>>.decayed == 1,
		is_same_as<vk::pipeline_bind_point>.decayed == 1
	>
	void cmd_bind_pipeline(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::command_buffer> command_buffer = a.template
			get_decayed_same_as<handle<vk::command_buffer>>();

		handle<vk::pipeline> pipeline = a.template
			get_decayed_same_as<handle<vk::pipeline>>();

		vk::pipeline_bind_point bind_point = a.template
			get_decayed_same_as<vk::pipeline_bind_point>();

		vk::get_device_function<vk::cmd_bind_pipeline_function>(
			instance, device
		)(
			command_buffer.underlying(),
			(int) bind_point,
			pipeline.underlying()
		);
	}

} // vk