#pragma once

#include "handle.hpp"

#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

#include "vk/device/handle.hpp"
#include "vk/result.hpp"
#include "vk/memory_offset.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::image>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device_memory>,
		types::are_may_contain_one_decayed<vk::memory_offset>
	>::for_types<Args...>
	vk::result try_bind_image_memory(Args&&... args) {
		auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);
		auto& image = elements::vk::possibly_guarded_handle_of<vk::image>(args...);
		auto& device_memory = elements::vk::possibly_guarded_handle_of<vk::device_memory>(args...);
		vk::memory_offset offset{ 0 };
		
		if constexpr(types::are_contain_decayed<vk::memory_offset>::for_types<Args...>) {
			offset = elements::decayed<vk::memory_offset>(args...);
		}

		return {
			(int32) vkBindImageMemory(
				(VkDevice) vk::get_handle_value(device),
				(VkImage) vk::get_handle_value(image),
				(VkDeviceMemory) vk::get_handle_value(device_memory),
				(VkDeviceSize) offset
			)
		};
	}

	template<typename... Args>
	void bind_image_memory(Args&&... args) {
		vk::result result = vk::try_bind_image_memory(forward<Args>(args)...);
		if(result.error()) vk::default_unexpected_handler(result);
	}

} // vk