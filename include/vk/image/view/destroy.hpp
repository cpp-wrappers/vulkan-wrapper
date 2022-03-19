#pragma once

#include "handle.hpp"

#include "vk/device/handle.hpp"
#include "vk/destroy_or_free.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::image_view> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_contain_one_decayed<handle<vk::image_view>>
		>::for_types<Args...>
		void operator () (Args&&... args) const {
			auto& device = elements::possibly_guarded_handle_of<vk::device>(args...);
			auto image_view = elements::decayed<handle<vk::image_view>>(args...);

			vkDestroyImageView(
				(VkDevice) vk::get_handle_value(device),
				(VkImageView) vk::get_handle_value(image_view),
				(VkAllocationCallbacks*) nullptr
			);
		}

	};

} // vk