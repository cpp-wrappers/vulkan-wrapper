#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>

#include "../../../shared/result.hpp"
#include "../../../shared/memory_offset.hpp"
#include "../../../shared/memory_size.hpp"
#include "../../device/handle.hpp"
#include "handle.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device_memory>,
		types::count_of_type<vk::memory_offset>::less_or_equals<1>,
		types::count_of_type<vk::memory_size>::equals<1>,
		types::count_of_type<void**>::equals<1>
	>::for_types_of<decay<Args>...>
	vk::result try_map_device_memory(Args&&... args) {
		auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);
		auto& device_memory = elements::vk::possibly_guarded_handle_of<vk::device_memory>(args...);
		vk::memory_offset offset{ 0 };

		if constexpr(types::are_contain_type<vk::memory_offset>::for_types_of<decay<Args>...>) {
			offset = elements::of_type<vk::memory_offset>(args...);
		}

		vk::memory_size size = elements::of_type<vk::memory_size>(args...);

		void** data = data = elements::of_type<void**>(args...);

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
		if(result.error()) default_unexpected_handler(result);
	}

} // vk