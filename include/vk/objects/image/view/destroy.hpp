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
			types::count_of_type<vk::handle<vk::image_view>>::equals<1>::ignore_const::ignore_reference
		>::for_types_of<Args...>
		void operator () (Args&&... args) const {
			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...);
			auto image_view = elements::of_type<vk::handle<vk::image_view>>::ignore_const::ignore_reference::for_elements_of(args...);

			vkDestroyImageView(
				(VkDevice) vk::get_handle_value(device),
				(VkImageView) vk::get_handle_value(image_view),
				(VkAllocationCallbacks*) nullptr
			);
		}

	};

} // vk