#pragma once

#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

#include "vk/device/handle.hpp"
#include "vk/memory_requirements.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::image>
	>::for_types<Args...>
	vk::memory_requirements get_image_memory_requirements(Args&&... args) {
		auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);
		auto& image = elements::vk::possibly_guarded_handle_of<vk::image>(args...);

		vk::memory_requirements memory_requirements;

		vkGetImageMemoryRequirements(
			(VkDevice) vk::get_handle_value(device),
			(VkImage) vk::get_handle_value(image),
			(VkMemoryRequirements*) &memory_requirements
		);

		return memory_requirements;
	}

} // vk