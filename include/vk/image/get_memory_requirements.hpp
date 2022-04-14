#pragma once

#include "../device/handle.hpp"
#include "../memory_requirements.hpp"
#include "../function.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

extern "C" VK_ATTR void VK_CALL vkGetImageMemoryRequirements(
	handle<vk::device> device,
	handle<vk::image> image,
	vk::memory_requirements* memory_requirements
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::device>>,
		types::are_contain_one_decayed<handle<vk::image>>
	>::for_types<Args...> [[nodiscard]]
	vk::memory_requirements
	get_image_memory_requirements(Args&&... args) {
		auto device = elements::decayed<handle<vk::device>>(args...);
		auto image = elements::decayed<handle<vk::image>>(args...);

		vk::memory_requirements memory_requirements;

		vkGetImageMemoryRequirements(
			device, image, &memory_requirements
		);

		return memory_requirements;

	} // get_image_memory_requirements

} // vk

vk::memory_requirements inline
handle<vk::device>::get_memory_requirements(handle<vk::image> image) const {
	return vk::get_image_memory_requirements(*this, image);
}