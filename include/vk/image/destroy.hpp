#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>

#include "../shared/destroy_or_free.hpp"
#include "../device/handle.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::image> {

		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::vk::contain_one<vk::device>,
				types::vk::contain_one<vk::image>
			>::for_types_of<Args...>
		)
		void operator () (Args&&... args) {
			auto& device = elements::vk::of_type<vk::device>::for_elements_of(args...);
			auto& image = elements::vk::of_type<vk::image>::for_elements_of(args...);

			vkDestroyImage(
				(VkDevice) vk::get_handle_value(device),
				(VkImage) vk::get_handle_value(image),
				(VkAllocationCallbacks*) nullptr
			);
		}
	};

}