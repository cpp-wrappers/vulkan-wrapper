#pragma once

#include "create_info.hpp"
#include "../component_mapping.hpp"
#include "../format.hpp"
#include "../subresource_range.hpp"
#include "handle.hpp"
#include "../../shared/create.hpp"

namespace vk {

	struct device;
	struct image_view;

	template<>
	struct vk::try_create_t<vk::image_view> {
		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::vk::contain_one<vk::device>,
				types::vk::contain_one<vk::image>,
				types::count_of_type<vk::format>::equals<1>::ignore_const::ignore_reference,
				types::count_of_type<vk::image_view_type>::equals<1>::ignore_const::ignore_reference,
				types::count_of_type<vk::component_mapping>::equals<1>::ignore_const::ignore_reference,
				types::count_of_type<vk::image_subresource_range>::equals<1>::ignore_const::ignore_reference
			>::for_types_of<Args...>
		)
		elements::one_of<vk::result, vk::handle<vk::image_view>>
		operator () (Args&&... args) const {
			auto& device = elements::vk::of_type<vk::device>::for_elements_of(args...);
			auto& image = elements::vk::of_type<vk::image>::for_elements_of(args...);

			vk::image_view_create_info ci {
				.image = vk::get_handle(image),
				.view_type = elements::of_type<vk::image_view_type>::ignore_const::ignore_reference::for_elements_of(args...),
				.format = elements::of_type<vk::format>::ignore_const::ignore_reference::for_elements_of(args...),
				.components = elements::of_type<vk::component_mapping>::ignore_const::ignore_reference::for_elements_of(args...),
				.subresource_range = elements::of_type<vk::image_subresource_range>::ignore_const::ignore_reference::for_elements_of(args...)
			};

			VkImage image_view;

			vk::result result {
				(int32) vkCreateImageView(
					(VkDevice) vk::get_handle_value(device),
					(VkImageViewCreateInfo*) &ci,
					nullptr,
					(VkImageView*) &image_view
				)
			};

			if(!result.success()) return result;

			return vk::handle<vk::image_view>{ image_view };
		}
	};
	
}