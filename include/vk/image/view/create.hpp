#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/of_type.hpp>

#include "../../result.hpp"
#include "create_info.hpp"
#include "vk/image/component_mapping.hpp"
#include "vk/image/format.hpp"
#include "vk/image/subresource_range.hpp"

namespace vk {

	struct device;
	struct image_view;

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::device&>::equals<1u>,
			types::count_of_type<vk::image&>::equals<1u>,
			types::count_of_type<vk::format>::remove_reference::equals<1u>,
			types::count_of_type<vk::image_view_type>::remove_reference::equals<1u>,
			types::count_of_type<vk::component_mapping>::remove_reference::equals<1u>,
			types::count_of_type<vk::image_subresource_range>::remove_reference::equals<1u>
		>::for_types_of<Args...>
	)
	vk::image_view& create_image_view(Args&&... args) {

		vk::device& device = elements::of_type<vk::device&>::for_elements_of(args...);

		vk::image_view_create_info ci {
			.image = elements::of_type<vk::image&>::for_elements_of(args...),
			.view_type = elements::of_type<vk::image_view_type>::remove_reference::for_elements_of(args...),
			.format = elements::of_type<vk::format>::remove_reference::for_elements_of(args...),
			.components = elements::of_type<vk::component_mapping>::remove_reference::for_elements_of(args...),
			.subresource_range = elements::of_type<vk::image_subresource_range>::remove_reference::for_elements_of(args...)
		};

		vk::image_view* image_view;

		vk::throw_if_error(
			vkCreateImageView(
				(VkDevice) &device,
				(VkImageViewCreateInfo*) &ci,
				nullptr,
				(VkImageView*) &image_view
			)
		);

		return *image_view;
	}
}