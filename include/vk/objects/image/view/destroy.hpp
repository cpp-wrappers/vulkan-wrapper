#pragma once

#include "../../../object/destroy_or_free.hpp"
#include "../../device/handle.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::image_view> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::count_of_type<vk::handle<vk::image_view>>::equals<1>
		>::for_types_of<decay<Args>...>
		void operator () (Args&&... args) const {
			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);
			auto image_view = elements::of_type<vk::handle<vk::image_view>>(args...);

			vkDestroyImageView(
				(VkDevice) vk::get_handle_value(device),
				(VkImageView) vk::get_handle_value(image_view),
				(VkAllocationCallbacks*) nullptr
			);
		}

	};

} // vk