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
		types::are_contain_one_decayed<handle<vk::device>>,
		types::are_contain_one_decayed<handle<vk::buffer>>
	>::for_types<Args...>
	vk::memory_requirements
	get_memory_requirements(Args&&... args) {
		auto buffer = elements::decayed<handle<vk::buffer>>(args...);
		auto device = elements::decayed<handle<vk::device>>(args...);

		vk::memory_requirements requirements;

		vkGetBufferMemoryRequirements(
			device,
			buffer,
			&requirements
		);

		return requirements;

	} // get_memory_requirements

} // vk

vk::memory_requirements inline
handle<vk::device>::get_memory_requirements(handle<vk::buffer> buffer) const {
	return vk::get_memory_requirements(*this, buffer);
}