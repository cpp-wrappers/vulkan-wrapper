#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>

#include "../../../shared/extent.hpp"
#include "../../../shared/viewport.hpp"
#include "handle.hpp"

namespace vk {

	struct first_viewport_index : wrapper::of_integer<uint32> {};

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::count_of_type<vk::first_viewport_index>::less_or_equals<1>::ignore_const::ignore_reference,
		types::count_of_ranges_of_value_type<vk::viewport>::equals<1>
	>::for_types_of<Args...>
	void cmd_set_viewport(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>::for_elements_of(args...);
		vk::first_viewport_index first{ 0 };
		
		if constexpr(types::are_contain_type<vk::first_viewport_index>::ignore_const::ignore_reference::for_types_of<Args...>) {
			first = elements::of_type<vk::first_viewport_index>::ignore_const::ignore_reference::for_elements_of(args...);
		}

		auto& viewports = elements::range_of_value_type<vk::viewport>::for_elements_of(args...);

		vkCmdSetViewport(
			(VkCommandBuffer) vk::get_handle_value(command_buffer),
			(uint32) first,
			(uint32) viewports.size(),
			(VkViewport*) viewports.data()
		);
	}

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::count_of_type<vk::first_viewport_index>::less_or_equals<1>::ignore_const::ignore_reference,
		types::count_of_type<vk::viewport>::equals<1>::ignore_const::ignore_reference
	>::for_types_of<Args...>
	void cmd_set_viewport(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>::for_elements_of(args...);
		vk::first_viewport_index first{ 0 };
		
		if constexpr(types::are_contain_type<vk::first_viewport_index>::ignore_const::ignore_reference::for_types_of<Args...>) {
			first = elements::of_type<vk::first_viewport_index>::ignore_const::ignore_reference::for_elements_of(args...);
		}

		vk::viewport viewport = elements::of_type<vk::viewport>::ignore_const::ignore_reference::for_elements_of(args...);

		vk::cmd_set_viewport(command_buffer, first, array{ viewport });
	}

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::count_of_type<vk::first_viewport_index>::less_or_equals<1>::ignore_const::ignore_reference,
		types::count_of_type<vk::extent<2>>::equals<1>::ignore_const::ignore_reference
	>::for_types_of<Args...>
	void cmd_set_viewport(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>::for_elements_of(args...);
		vk::first_viewport_index first{ 0 };
		
		if constexpr(types::are_contain_type<vk::first_viewport_index>::ignore_const::ignore_reference::for_types_of<Args...>) {
			first = elements::of_type<vk::first_viewport_index>::ignore_const::ignore_reference::for_elements_of(args...);
		}

		vk::extent<2> extent = elements::of_type<vk::extent<2>>::ignore_const::ignore_reference::for_elements_of(args...);

		vk::cmd_set_viewport(
			command_buffer,
			first,
			vk::viewport {
				.width = float(extent.width()),
				.height = float(extent.height())
			}
		);
	}

} // vk