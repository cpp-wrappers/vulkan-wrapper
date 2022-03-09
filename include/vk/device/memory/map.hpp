#pragma once

#include "handle.hpp"

#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

#include "vk/device/handle.hpp"
#include "vk/result.hpp"
#include "vk/memory_offset.hpp"
#include "vk/memory_size.hpp"
#include "vk/default_unexpected_handler.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device_memory>,
		types::are_may_contain_one_decayed<vk::memory_offset>,
		types::are_contain_one_decayed<vk::memory_size>,
		types::are_contain_one_decayed<void**>
	>::for_types<Args...>
	vk::result try_map_device_memory(Args&&... args) {
		auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);
		auto& device_memory = elements::vk::possibly_guarded_handle_of<vk::device_memory>(args...);
		vk::memory_offset offset{ 0 };

		if constexpr(types::are_contain_decayed<vk::memory_offset>::for_types<Args...>) {
			offset = elements::decayed<vk::memory_offset>(args...);
		}

		vk::memory_size size = elements::decayed<vk::memory_size>(args...);

		void** data = data = elements::decayed<void**>(args...);

		return {
			(int32) vkMapMemory(
				(VkDevice) vk::get_handle_value(device),
				(VkDeviceMemory) vk::get_handle_value(device_memory),
				(VkDeviceSize) offset,
				(VkDeviceSize) size,
				(VkMemoryMapFlags) 0,
				data
			)
		};
	}

	template<typename... Args>
	void map_device_memory(Args&&... args) {
		vk::result result = vk::try_map_device_memory(forward<Args>(args)...);
		if(result.error()) vk::default_unexpected_handler(result);
	}

} // vk