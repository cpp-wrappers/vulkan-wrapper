#pragma once

#include "../../shared/first_binding.hpp"
#include "cmd_bind_vertex_buffers.hpp"

namespace vk {
	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::vk::contain_one<vk::command_buffer>,
			types::count_of_type<vk::first_binding>::less_or_equals<1>::ignore_const::ignore_reference,
			types::vk::contain_one<vk::buffer>,
			types::count_of_type<vk::memory_offset>::less_or_equals<1>::ignore_const::ignore_reference
		>::for_types_of<Args...>
	)
	void cmd_bind_vertex_buffer(Args&&... args) {
		auto& command_buffer = elements::vk::of_type<vk::command_buffer>::for_elements_of(args...);
		vk::handle<vk::buffer> buffer = vk::get_handle(elements::vk::of_type<vk::buffer>::for_elements_of(args...));

		vk::first_binding binding{ 0 };

		if constexpr(types::are_contain_type<vk::first_binding>::ignore_const::ignore_reference::for_types_of<Args...>) {
			binding = elements::of_type<vk::first_binding>::ignore_const::ignore_reference::for_elements_of(args...);
		} 

		vk::memory_offset offset{ 0 };

		if constexpr(types::are_contain_type<vk::memory_offset>::ignore_const::ignore_reference::for_types_of<Args...>) {
			offset = elements::of_type<vk::memory_offset>::ignore_const::ignore_reference::for_elements_of(args...);
		}
		
		vk::cmd_bind_vertex_buffers(
			command_buffer,
			binding,
			array{ buffer },
			array{ offset }
		);
	}
}