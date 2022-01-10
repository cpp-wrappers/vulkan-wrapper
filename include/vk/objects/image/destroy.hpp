#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>

#include "../../types/are_contain_one_possibly_guarded_handle_of.hpp"
#include "../../elements/possibly_guarded_handle_of.hpp"
#include "../../object/destroy_or_free.hpp"
#include "../device/handle.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::image> {

		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
				types::vk::are_contain_one_possibly_guarded_handle_of<vk::image>
			>::for_types_of<Args...>
		)
		void operator () (Args&&... args) {
			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...);
			auto& image = elements::vk::possibly_guarded_handle_of<vk::image>::for_elements_of(args...);

			vkDestroyImage(
				(VkDevice) vk::get_handle_value(device),
				(VkImage) vk::get_handle_value(image),
				(VkAllocationCallbacks*) nullptr
			);
		}
	};

}