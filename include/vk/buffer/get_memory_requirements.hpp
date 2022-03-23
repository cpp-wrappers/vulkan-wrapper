#pragma once

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

#include "vk/device/handle.hpp"
#include "vk/memory_requirements_2.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_contain_one_possibly_guarded_handle_of<vk::buffer>
	>::for_types<Args...>
	vk::memory_requirements
	get_memory_requirements(Args&&... args) {
		auto& buffer = elements::possibly_guarded_handle_of<vk::buffer>(args...);
		auto& device = elements::possibly_guarded_handle_of<vk::device>(args...);

		vk::memory_requirements mr;

		vkGetBufferMemoryRequirements(
			(VkDevice) vk::get_handle_value(device),
			(VkBuffer) vk::get_handle_value(buffer),
			(VkMemoryRequirements*) &mr
		);

		return mr;
	}

} // vk