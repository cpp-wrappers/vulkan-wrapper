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
		is_convertible_to<handle<vk::instance>> == 1,
		is_convertible_to<handle<vk::device>> == 1,
		is_convertible_to<handle<vk::command_buffer>> == 1,
		is_convertible_to<handle<vk::pipeline>> == 1,
		is_same_as<vk::pipeline_bind_point>.decayed == 1
	>
	void cmd_bind_pipeline(Args&&... args) {
		tuple a { args... };

		auto instance = (handle<vk::instance>) a.template
			get<is_convertible_to<handle<vk::instance>>>();

		auto device = (handle<vk::device>) a.template
			get<is_convertible_to<handle<vk::device>>>();

		auto command_buffer = (handle<vk::command_buffer>) a.template
			get<is_convertible_to<handle<vk::command_buffer>>>();

		auto pipeline = (handle<vk::pipeline>) a.template
			get<is_convertible_to<handle<vk::pipeline>>>();

		vk::pipeline_bind_point bind_point = a.template
			get<is_same_as<vk::pipeline_bind_point>.decayed>();

		vk::get_device_function<vk::cmd_bind_pipeline_function>(
			instance, device
		)(
			command_buffer.underlying(),
			(int) bind_point,
			pipeline.underlying()
		);
	}

} // vk