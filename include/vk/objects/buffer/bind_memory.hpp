#pragma once

#include "handle.hpp"
#include "../device/handle.hpp"
#include "../../shared/result.hpp"
#include "../../shared/memory_offset.hpp"
#include "../../types/are_contain_one_possibly_guarded_handle_of.hpp"
#include "../../elements/possibly_guarded_handle_of.hpp"

#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::buffer>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device_memory>,
		types::are_may_contain_one_decayed_same_as<vk::memory_offset>
	>::for_types<Args...>
	vk::result try_bind_buffer_memory(Args&&... args) {
		auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);
		auto& buffer = elements::vk::possibly_guarded_handle_of<vk::buffer>(args...);
		auto& device_memory = elements::vk::possibly_guarded_handle_of<vk::device_memory>(args...);
		vk::memory_offset offset{ 0 };
		
		if constexpr(types::are_contain_decayed_same_as<vk::memory_offset>::for_types<Args...>) {
			offset = elements::decayed_same_as<vk::memory_offset>(args...);
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
		if(result.error()) default_unexpected_handler(result);
	}

} // vk