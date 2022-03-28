#pragma once

#include "../device/handle.hpp"
#include "../memory_requirements_2.hpp"
#include "../function.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

extern "C" VK_ATTR void VK_CALL vkGetBufferMemoryRequirements(
	handle<vk::device> device,
	handle<vk::buffer> buffer,
	vk::memory_requirements* memory_requirements
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_contain_one_possibly_guarded_handle_of<vk::buffer>
	>::for_types<Args...>
	vk::memory_requirements
	get_memory_requirements(Args&&... args) {
		auto& buffer = elements::possibly_guarded_handle_of<
			vk::buffer
		>(args...);

		auto& device = elements::possibly_guarded_handle_of<
			vk::device
		>(args...);

		vk::memory_requirements mr;

		vkGetBufferMemoryRequirements(
			vk::get_handle(device),
			vk::get_handle(buffer),
			&mr
		);

		return mr;

	} // get_memory_requirements

} // vk