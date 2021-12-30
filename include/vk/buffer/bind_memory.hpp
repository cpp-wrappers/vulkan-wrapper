#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>

#include "../shared/result.hpp"
#include "../device/handle.hpp"
#include "../shared/guarded_handle.hpp"
#include "../shared/memory_offset.hpp"
#include "handle.hpp"

namespace vk {

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::vk::contain_one<vk::device>,
			types::vk::contain_one<vk::buffer>,
			types::vk::contain_one<vk::device_memory>,
			types::count_of_type<vk::memory_offset>::less_or_equals<1>::ignore_const::ignore_reference
		>::for_types_of<Args...>
	)
	vk::result try_bind_buffer_memory(Args&&... args) {
		auto& device = elements::vk::of_type<vk::device>::for_elements_of(args...);
		auto& buffer = elements::vk::of_type<vk::buffer>::for_elements_of(args...);
		auto& device_memory = elements::vk::of_type<vk::device_memory>::for_elements_of(args...);
		vk::memory_offset offset{ 0 };
		
		if constexpr(types::are_contain_type<vk::memory_offset>::ignore_const::ignore_reference::for_types_of<Args...>) {
			offset = elements::of_type<vk::memory_offset>::ignore_const::ignore_reference::for_elements_of(args...);
		}

		return {
			(int32) vkBindBufferMemory(
				(VkDevice) vk::get_handle_value(device),
				(VkBuffer) vk::get_handle_value(buffer),
				(VkDeviceMemory) vk::get_handle_value(device_memory),
				(VkDeviceSize) offset
			)
		};
	}

	template<typename... Args>
	void bind_buffer_memory(Args&&... args) {
		vk::result result = vk::try_bind_buffer_memory(forward<Args>(args)...);
		if(!result.success()) throw result;
	}
}