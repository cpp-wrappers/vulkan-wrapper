#pragma once

#include "handle.hpp"
#include "../../buffer/handle.hpp"
#include "../../first_binding.hpp"
#include "../../memory_offset.hpp"
#include "../../headers.hpp"
#include "../../handle/get_value.hpp"

#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

namespace vk {

	struct command_buffer;

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_may_contain_one_decayed_same_as<vk::first_binding>,
		types::are_contain_one_range_of_value_type<vk::handle<vk::buffer>>,
		types::are_contain_one_range_of_value_type<vk::memory_offset>
	>::for_types<Args...>
	void cmd_bind_vertex_buffers(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>(args...);
		
		vk::first_binding first_binding{ 0 };
		if constexpr(types::are_contain_decayed_same_as<vk::first_binding>::for_types<Args...>) {
			first_binding = elements::decayed_same_as<vk::first_binding>(args...);
		}

		auto& buffers = elements::range_of_value_type<vk::handle<vk::buffer>>(args...);
		auto& offsets = elements::range_of_value_type<vk::memory_offset>(args...);

		vkCmdBindVertexBuffers(
			(VkCommandBuffer) vk::get_handle_value(command_buffer),
			(uint32) first_binding,
			(uint32) buffers.size(),
			(VkBuffer*) buffers.data(),
			(VkDeviceSize*) offsets.data()
		);
	}

} // vk

template<typename... Args> 
auto& vk::handle<vk::command_buffer>::cmd_bind_vertex_buffers(Args&&... args) const {
	vk::cmd_bind_vertex_buffers(*this, forward<Args>(args)...);
	return *this;
}