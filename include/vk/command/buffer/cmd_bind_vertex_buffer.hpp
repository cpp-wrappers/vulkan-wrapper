#pragma once

#include "cmd_bind_vertex_buffers.hpp"

#include <core/array.hpp>

#include "vk/first_binding.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_contain_one_possibly_guarded_handle_of<vk::buffer>,
		types::are_may_contain_one_decayed<vk::first_binding>,
		types::are_may_contain_one_decayed<vk::memory_offset>
	>::for_types<Args...>
	void cmd_bind_vertex_buffer(Args&&... args) {
		auto& command_buffer = elements::possibly_guarded_handle_of<vk::command_buffer>(args...);
		handle<vk::buffer> buffer = vk::get_handle(elements::possibly_guarded_handle_of<vk::buffer>(args...));

		vk::first_binding binding{ 0 };

		if constexpr(types::are_contain_decayed<vk::first_binding>::for_types<Args...>) {
			binding = elements::decayed<vk::first_binding>(args...);
		} 

		vk::memory_offset offset{ 0 };

		if constexpr(types::are_contain_decayed<vk::memory_offset>::for_types<Args...>) {
			offset = elements::decayed<vk::memory_offset>(args...);
		}
		
		vk::cmd_bind_vertex_buffers(
			command_buffer,
			binding,
			array{ buffer },
			array{ offset }
		);
	}

} // vk

template<typename... Args> 
auto& handle<vk::command_buffer>::cmd_bind_vertex_buffer(Args&&... args) const {
	vk::cmd_bind_vertex_buffer(*this, forward<Args>(args)...);
	return *this;
}