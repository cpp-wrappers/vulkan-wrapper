#pragma once

#include <core/wrapper/of_integer.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>

#include "../../buffer/handle.hpp"
#include "../../shared/first_binding.hpp"
#include "../../shared/memory_offset.hpp"
#include "handle.hpp"

namespace vk {

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::vk::contain_one<vk::command_buffer>,
			types::count_of_type<vk::first_binding>::less_or_equals<1>::ignore_const::ignore_reference,
			types::count_of_ranges_of_value_type<vk::handle<vk::buffer>>::equals<1>,
			types::count_of_ranges_of_value_type<vk::memory_offset>::equals<1>
		>::for_types_of<Args...>
	)
	void cmd_bind_vertex_buffers(Args&&... args) {
		auto& command_buffer = elements::vk::of_type<vk::command_buffer>::for_elements_of(args...);
		
		vk::first_binding first_binding{ 0 };
		if constexpr(types::are_contain_type<vk::first_binding>::ignore_const::ignore_reference::for_types_of<Args...>) {
			first_binding = elements::of_type<vk::first_binding>::ignore_const::ignore_reference::for_elements_of(args...);
		}

		auto& buffers = elements::range_of_value_type<vk::handle<vk::buffer>>::for_elements_of(args...);
		auto& offsets = elements::range_of_value_type<vk::memory_offset>::for_elements_of(args...);

		vkCmdBindVertexBuffers(
			(VkCommandBuffer) vk::get_handle_value(command_buffer),
			(uint32) first_binding,
			(uint32) buffers.size(),
			(VkBuffer*) buffers.data(),
			(VkDeviceSize*) offsets.data()
		);
	}
}