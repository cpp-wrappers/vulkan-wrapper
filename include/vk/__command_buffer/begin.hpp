#pragma once

#include "./handle.hpp"
#include "./begin_info.hpp"
#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/result.hpp"
#include "../__internal/unexpected_handler.hpp"

#include <tuple.hpp>

namespace vk {

	struct begin_command_buffer_function : vk::function<int32(*)(
		handle<vk::command_buffer>::underlying_type command_buffer,
		const vk::command_buffer_begin_info* begin_info
	)> {
		static constexpr auto name = "vkBeginCommandBuffer";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::command_buffer>> == 1,
		count_of_decayed_same_as<vk::command_buffer_usages> <= 1,
		count_of_decayed_same_as<vk::command_buffer_inheritance_info> <= 1
	>
	vk::result try_begin_command_buffer(Args&&... args) {
		tuple a { args... };
		vk::command_buffer_begin_info bi {};

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::command_buffer_usages> > 0
		) {
			bi.usages = a.template
				get_decayed_same_as<vk::command_buffer_usages>();
		}

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::command_buffer_inheritance_info> > 0
		) {
			bi.inheritance_info = a.template
				get_decayed_same_as<vk::command_buffer_inheritance_info>();
		}

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::command_buffer> command_buffer = a.template
			get_decayed_same_as<handle<vk::command_buffer>>();

		return {
			vk::get_device_function<vk::begin_command_buffer_function>(
				instance, device
			)(
				command_buffer.underlying(), &bi
			)
		};
	}

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::command_buffer>> == 1,
		count_of_decayed_same_as<vk::command_buffer_usages> == 1,
		count_of_decayed_same_as<handle<vk::render_pass>> == 1,
		count_of_decayed_same_as<handle<vk::framebuffer>> == 1,
		count_of_decayed_same_as<vk::subpass> == 1,
		count_of_decayed_same_as<vk::occlusion_query_enable> <= 1,
		count_of_decayed_same_as<vk::query_control_flags> == 1,
		count_of_decayed_same_as<vk::query_pipeline_statistic_flags> == 1
	>
	vk::result try_begin_command_buffer(Args&&... args) {
		tuple a { args... };
		vk::command_buffer_inheritance_info ii {
			.render_pass = a.template
				get_decayed_same_as<vk::command_buffer>(),
			.subpass = a.template get_decayed_same_as<vk::subpass>(),
			.framebuffer = a.template get_decayed_same_as<vk::framebuffer>(),
			.query_flags = a.template
				get_decayed_same_as<vk::query_control_flags>(),
			.pipeline_statistics_flags = a.template
				get_decayed_same_as<vk::query_pipeline_statistic_flags>()
		};

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::occlusion_query_enable> > 0
		) {
			ii.occlusion_query_enable = a.template
				get_decayed_same_as<vk::occlusion_query_enable>();
		}

		vk::command_buffer_usages usages = a.template
			get_decayed_same_as<vk::command_buffer_usages>();

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::command_buffer> command_buffer = a.template
			get_decayed_same_as<handle<vk::command_buffer>>();

		return vk::try_begin_command_buffer(
			instance, device, command_buffer, usages, ii
		);
	}

	template<typename... Args>
	void begin_command_buffer(Args&&... args) {
		vk::result result {
			vk::try_begin_command_buffer(forward<Args>(args)...)
		};

		if(result.error()) vk::unexpected_handler(result);
	}

} // vk