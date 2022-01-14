#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>

#include "../../../shared/rect2d.hpp"
#include "handle.hpp"

namespace vk {

	struct first_scissor_index : wrapper::of_integer<uint32> {};

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::count_of_type<vk::first_scissor_index>::less_or_equals<1>::ignore_const::ignore_reference,
		types::count_of_ranges_of_value_type<vk::rect2d>::equals<1>
	>::for_types_of<Args...>
	void cmd_set_scissor(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>::for_elements_of(args...);
		vk::first_scissor_index first{ 0 };
		
		if constexpr(types::are_contain_type<vk::first_scissor_index>::ignore_const::ignore_reference::for_types_of<Args...>) {
			first = elements::of_type<vk::first_scissor_index>::ignore_const::ignore_reference::for_elements_of(args...);
		}

		auto& scissors = elements::range_of_value_type<vk::rect2d>::for_elements_of(args...);

		vkCmdSetScissor(
			(VkCommandBuffer) vk::get_handle_value(command_buffer),
			(uint32) first,
			(uint32) scissors.size(),
			(VkRect2D*) scissors.data()
		);
	}

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::count_of_type<vk::first_scissor_index>::less_or_equals<1>::ignore_const::ignore_reference,
		types::count_of_type<vk::rect2d>::equals<1>::ignore_const::ignore_reference
	>::for_types_of<Args...>
	void cmd_set_scissor(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>::for_elements_of(args...);
		vk::first_scissor_index first{ 0 };
		
		if constexpr(types::are_contain_type<vk::first_scissor_index>::ignore_const::ignore_reference::for_types_of<Args...>) {
			first = elements::of_type<vk::first_scissor_index>::ignore_const::ignore_reference::for_elements_of(args...);
		}

		vk::rect2d scissor = elements::of_type<vk::rect2d>::ignore_const::ignore_reference::for_elements_of(args...);

		vk::cmd_set_scissor(command_buffer, first, array{ scissor });
	}

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::count_of_type<vk::first_scissor_index>::less_or_equals<1>::ignore_const::ignore_reference,
		types::count_of_type<vk::extent<2>>::equals<1>::ignore_const::ignore_reference
	>::for_types_of<Args...>
	void cmd_set_scissor(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>::for_elements_of(args...);
		vk::first_scissor_index first{ 0 };
		
		if constexpr(types::are_contain_type<vk::first_scissor_index>::ignore_const::ignore_reference::for_types_of<Args...>) {
			first = elements::of_type<vk::first_scissor_index>::ignore_const::ignore_reference::for_elements_of(args...);
		}

		vk::extent<2> extent  = elements::of_type<vk::extent<2>>::ignore_const::ignore_reference::for_elements_of(args...);

		vk::cmd_set_scissor(command_buffer, first, vk::rect2d{ .extent{ extent } } );
	}

} // vk