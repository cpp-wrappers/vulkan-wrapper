#pragma once

#include "handle.hpp"

#include "../../function.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

namespace vk {

	struct vertex_count   { uint32 _; };
	struct instance_count { uint32 _; };
	struct first_vertex   { uint32 _; };
	struct first_instance { uint32 _; };

}

extern "C" VK_ATTR void VK_CALL vkCmdDraw(
	handle<vk::command_buffer> commandBuffer,
	vk::vertex_count           vertex_count,
	vk::instance_count         instance_count,
	vk::first_vertex           first_vertex,
	vk::first_instance         first_instance
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::command_buffer>>,
		types::are_contain_one_decayed<vk::vertex_count>,
		types::are_may_contain_one_decayed<vk::instance_count>,
		types::are_may_contain_one_decayed<vk::first_vertex>,
		types::are_may_contain_one_decayed<vk::first_instance>
	>::for_types<Args...>
	void cmd_draw(Args&&... args) {
		auto command_buffer {
			elements::decayed<handle<vk::command_buffer>>(args...)
		};

		vk::vertex_count vertex_count {
			elements::decayed<vk::vertex_count>(args...)
		};

		vk::instance_count instance_count{ 1 };

		if constexpr (
			types::are_contain_decayed<vk::instance_count>::for_types<Args...>
		) { instance_count = elements::decayed<vk::instance_count>(args...); }

		vk::first_vertex first_vertex{ 0 };

		if constexpr (
			types::are_contain_decayed<vk::first_vertex>::for_types<Args...>
		) { first_vertex = elements::decayed<vk::first_vertex>(args...); }

		vk::first_instance first_instance{ 0 };

		if constexpr (
			types::are_contain_decayed<vk::first_instance>::for_types<Args...>
		) { first_instance = elements::decayed<vk::first_instance>(args...); }

		vkCmdDraw(
			command_buffer,
			vertex_count,
			instance_count,
			first_vertex,
			first_instance
		);
	} // cmd_draw

} // vk

template<typename... Args>
auto& handle<vk::command_buffer>::cmd_draw(Args&&... args) const {
	vk::cmd_draw(*this, forward<Args>(args)...);
	return *this;
}