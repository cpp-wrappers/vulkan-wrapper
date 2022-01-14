#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/wrapper/of_integer.hpp>

#include "handle.hpp"

namespace vk {

	struct vertex_count : wrapper::of_integer<uint32, struct vertex_count_t>{};
	struct instance_count : wrapper::of_integer<uint32, struct instance_count_t>{};
	struct first_vertex : wrapper::of_integer<uint32, struct first_vertex_t>{};
	struct first_instance : wrapper::of_integer<uint32, struct first_instance_t>{};

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::count_of_type<vk::vertex_count>::equals<1>::ignore_const::ignore_reference,
		types::count_of_type<vk::instance_count>::less_or_equals<1>::ignore_const::ignore_reference,
		types::count_of_type<vk::first_vertex>::less_or_equals<1>::ignore_const::ignore_reference,
		types::count_of_type<vk::first_instance>::less_or_equals<1>::ignore_const::ignore_reference
	>::for_types_of<Args...>
	void cmd_draw(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>::for_elements_of(args...);

		vk::vertex_count vertex_count = elements::of_type<vk::vertex_count>::ignore_const::ignore_reference::for_elements_of(args...);
		vk::instance_count instance_count{ 1 };

		if constexpr(types::are_contain_type<vk::instance_count>::ignore_const::ignore_reference::for_types_of<Args...>) {
			instance_count = elements::of_type<vk::instance_count>::ignore_const::ignore_reference::for_elements_of(args...);
		}

		vk::first_vertex first_vertex{ 0 };

		if constexpr(types::are_contain_type<vk::first_vertex>::ignore_const::ignore_reference::for_types_of<Args...>) {
			first_vertex = elements::of_type<vk::first_vertex>::ignore_const::ignore_reference::for_elements_of(args...);
		}

		vk::first_instance first_instance{ 0 };

		if constexpr(types::are_contain_type<vk::first_instance>::ignore_const::ignore_reference::for_types_of<Args...>) {
			first_instance = elements::of_type<vk::first_instance>::ignore_const::ignore_reference::for_elements_of(args...);
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