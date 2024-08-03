#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	enum vertex_count : uint32{};
	enum instance_count : uint32{};
	enum first_vertex : uint32{};
	enum first_instance : uint32{};

}

namespace vk {

	struct cmd_draw_function : vk::function<void(*)(
		handle<vk::command_buffer>::underlying_type commandBuffer,
		uint32 /*vk::vertex_count*/ vertex_count,
		uint32 /*vk::instance_count*/ instance_count,
		uint32 /*vk::first_vertex*/ first_vertex,
		uint32 /*vk::first_instance*/ first_instance
	)> {
		static constexpr auto name = "vkCmdDraw";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::command_buffer>>.decayed == 1,
		is_same_as<vk::vertex_count>.decayed == 1,
		is_same_as<vk::instance_count>.decayed <= 1,
		is_same_as<vk::first_vertex>.decayed <= 1,
		is_same_as<vk::first_instance>.decayed <= 1
	>
	void cmd_draw(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::command_buffer> command_buffer = a.template
			get<is_same_as<handle<vk::command_buffer>>.decayed>();

		vk::vertex_count vertex_count = a.template
			get<is_same_as<vk::vertex_count>.decayed>();

		vk::instance_count instance_count{ 1 };

		if constexpr (
			(is_same_as<vk::instance_count>.decayed > 0)
			.for_types<Args...>()
		) {
			instance_count = a.template
				get<is_same_as<vk::instance_count>.decayed>();
		}

		vk::first_vertex first_vertex{ 0 };

		if constexpr (
			(is_same_as<vk::first_vertex>.decayed > 0)
			.for_types<Args...>()
		) {
			first_vertex = a.template
				get<is_same_as<handle<vk::first_vertex>>.decayed>();
		}

		vk::first_instance first_instance{ 0 };

		if constexpr (
			(is_same_as<vk::first_instance>.decayed > 0)
			.for_types<Args...>()
		) {
			first_instance = a.template
				get<is_same_as<handle<vk::first_instance>>.decayed>();
		}

		vk::get_device_function<vk::cmd_draw_function>(
			instance, device
		)(
			command_buffer.underlying(),
			vertex_count,
			instance_count,
			first_vertex,
			first_instance
		);
	} // cmd_draw

} // vk