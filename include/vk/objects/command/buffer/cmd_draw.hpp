#pragma once

#include "handle.hpp"

#include <core/wrapper/of_integer.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

namespace vk {

	struct vertex_count : wrapper::of_integer<uint32, struct vertex_count_t>{};
	struct instance_count : wrapper::of_integer<uint32, struct instance_count_t>{};
	struct first_vertex : wrapper::of_integer<uint32, struct first_vertex_t>{};
	struct first_instance : wrapper::of_integer<uint32, struct first_instance_t>{};

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_contain_one_decayed_same_as<vk::vertex_count>,
		types::are_may_contain_one_decayed_same_as<vk::instance_count>,
		types::are_may_contain_one_decayed_same_as<vk::first_vertex>,
		types::are_may_contain_one_decayed_same_as<vk::first_instance>
	>::for_types<Args...>
	void cmd_draw(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>(args...);

		vk::vertex_count vertex_count = elements::decayed_same_as<vk::vertex_count>(args...);
		vk::instance_count instance_count{ 1 };

		if constexpr(types::are_contain_decayed_same_as<vk::instance_count>::for_types<Args...>) {
			instance_count = elements::decayed_same_as<vk::instance_count>(args...);
		}

		vk::first_vertex first_vertex{ 0 };

		if constexpr(types::are_contain_decayed_same_as<vk::first_vertex>::for_types<Args...>) {
			first_vertex = elements::decayed_same_as<vk::first_vertex>(args...);
		}

		vk::first_instance first_instance{ 0 };

		if constexpr(types::are_contain_decayed_same_as<vk::first_instance>::for_types<Args...>) {
			first_instance = elements::decayed_same_as<vk::first_instance>(args...);
		}

		vkCmdDraw(
			(VkCommandBuffer) vk::get_handle_value(command_buffer),
			(uint32) vertex_count,
			(uint32) instance_count,
			(uint32) first_vertex,
			(uint32) first_instance
		);
	}

} // vk