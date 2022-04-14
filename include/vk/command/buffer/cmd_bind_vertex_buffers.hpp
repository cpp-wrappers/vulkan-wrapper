#pragma once

#include "handle.hpp"

#include "../../buffer/handle.hpp"
#include "../../first_binding.hpp"
#include "../../memory_offset.hpp"
#include "../../function.hpp"

#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

extern "C" VK_ATTR void VK_CALL vkCmdBindVertexBuffers(
	handle<vk::command_buffer> command_buffer,
	uint32 first_binding,
	uint32 binding_count,
	const handle<vk::buffer>* buffers,
	const vk::memory_offset* offsets
);

namespace vk {

	struct command_buffer;

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::command_buffer>>,
		types::are_may_contain_one_decayed<vk::first_binding>,
		types::are_contain_range_of<handle<vk::buffer>>,
		types::are_contain_range_of<vk::memory_offset>
	>::for_types<Args...>
	void cmd_bind_vertex_buffers(Args&&... args) {
		auto command_buffer {
			elements::decayed<handle<vk::command_buffer>>(args...)
		};
		
		vk::first_binding first_binding{ 0 };

		if constexpr (
			types::are_contain_decayed<vk::first_binding>::for_types<Args...>
		) { first_binding = elements::decayed<vk::first_binding>(args...); }

		auto& buffers = elements::range_of<handle<vk::buffer>>(args...);
		auto& offsets = elements::range_of<vk::memory_offset>(args...);

		vkCmdBindVertexBuffers(
			command_buffer,
			(uint32) first_binding,
			(uint32) buffers.size(),
			buffers.data(),
			offsets.data()
		);
	}

} // vk

template<typename... Args> 
auto&
handle<vk::command_buffer>::cmd_bind_vertex_buffers(Args&&... args) const {
	vk::cmd_bind_vertex_buffers(*this, forward<Args>(args)...);
	return *this;
}