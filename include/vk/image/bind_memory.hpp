#pragma once

#include "handle.hpp"
#include "../device/handle.hpp"
#include "../result.hpp"
#include "../memory_offset.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_contain_one_possibly_guarded_handle_of<vk::image>,
		types::are_contain_one_possibly_guarded_handle_of<vk::device_memory>,
		types::are_may_contain_one_decayed<vk::memory_offset>
	>::for_types<Args...> [[nodiscard]]
	vk::result try_bind_image_memory(Args&&... args) {
		auto& device {
			elements::possibly_guarded_handle_of<vk::device>(args...)
		};
		auto& image {
			elements::possibly_guarded_handle_of<vk::image>(args...)
		};
		auto& device_memory {
			elements::possibly_guarded_handle_of<vk::device_memory>(args...)
		};

		vk::memory_offset offset{ 0 };
		
		if constexpr (
			types::are_contain_decayed<vk::memory_offset>::for_types<Args...>
		) { offset = elements::decayed<vk::memory_offset>(args...); }

		return {
			(int32) vkBindImageMemory(
				(VkDevice) vk::get_handle_value(device),
				(VkImage) vk::get_handle_value(image),
				(VkDeviceMemory) vk::get_handle_value(device_memory),
				(VkDeviceSize) offset
			)
		};
	} // try_bind_image_memory

	template<typename... Args>
	void bind_image_memory(Args&&... args) {
		vk::result result = vk::try_bind_image_memory(forward<Args>(args)...);
		if(result.error()) vk::unexpected_handler(result);
	}

} // vk