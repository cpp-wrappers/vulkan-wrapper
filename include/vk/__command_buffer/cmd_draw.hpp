#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct vertex_count   { uint32 _; };
	struct instance_count { uint32 _; };
	struct first_vertex   { uint32 _; };
	struct first_instance { uint32 _; };

}

namespace vk {

	struct cmd_draw_function : vk::function<void(*)(
		handle<vk::command_buffer>::underlying_type commandBuffer,
		vk::vertex_count vertex_count,
		vk::instance_count instance_count,
		vk::first_vertex first_vertex,
		vk::first_instance first_instance
	)> {
		static constexpr auto name = "vkCmdDraw";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::command_buffer>> == 1,
		count_of_decayed_same_as<vk::vertex_count> == 1,
		count_of_decayed_same_as<vk::instance_count> <= 1,
		count_of_decayed_same_as<vk::first_vertex> <= 1,
		count_of_decayed_same_as<vk::first_instance> <= 1
	>
	void cmd_draw(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::command_buffer> command_buffer = a.template
			get_decayed_same_as<handle<vk::command_buffer>>();

		vk::vertex_count vertex_count = a.template
			get_decayed_same_as<vk::vertex_count>();

		vk::instance_count instance_count{ 1 };

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::instance_count> > 0
		) {
			instance_count = a.template
				get_decayed_same_as<vk::instance_count>();
		}

		vk::first_vertex first_vertex{ 0 };

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::first_vertex> > 0
		) {
			first_vertex = a.template
				get_decayed_same_as<handle<vk::first_vertex>>();
		}

		vk::first_instance first_instance{ 0 };

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::first_instance> > 0
		) {
			first_instance = a.template
				get_decayed_same_as<handle<vk::first_instance>>();
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