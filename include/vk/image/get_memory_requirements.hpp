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
		types::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_contain_one_possibly_guarded_handle_of<vk::image>
	>::for_types<Args...> [[nodiscard]]
	vk::memory_requirements
	get_image_memory_requirements(Args&&... args) {
		auto& device {
			elements::possibly_guarded_handle_of<vk::device>(args...)
		};
		auto& image {
			elements::possibly_guarded_handle_of<vk::image>(args...)
		};

		vk::memory_requirements memory_requirements;

		vkGetImageMemoryRequirements(
			vk::get_handle(device),
			vk::get_handle(image),
			&memory_requirements
		);

		return memory_requirements;

	} // get_image_memory_requirements

} // vk