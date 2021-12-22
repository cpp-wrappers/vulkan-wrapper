#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/one_of.hpp>

#include "../../shared/result.hpp"
#include "create_info.hpp"
#include "../component_mapping.hpp"
#include "../format.hpp"
#include "../subresource_range.hpp"
#include "../../device/handle.hpp"
#include "handle.hpp"

namespace vk {

	struct device;
	struct image_view;

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::handle<vk::device>>::equals<1>,
			types::count_of_type<vk::handle<vk::image>>::equals<1>,
			types::count_of_type<vk::format>::equals<1>,
			types::count_of_type<vk::image_view_type>::equals<1>,
			types::count_of_type<vk::component_mapping>::equals<1>,
			types::count_of_type<vk::image_subresource_range>::equals<1>
		>::for_types_of<Args...>
	)
	elements::one_of<vk::result, vk::handle<vk::image_view>>
	try_create_image_view(Args... args) {
		vk::handle<vk::device> device = elements::of_type<vk::handle<vk::device>&>::for_elements_of(args...);

		vk::image_view_create_info ci {
			.image = elements::of_type<vk::handle<vk::image>&>::for_elements_of(args...),
			.view_type = elements::of_type<vk::image_view_type&>::for_elements_of(args...),
			.format = elements::of_type<vk::format&>::for_elements_of(args...),
			.components = elements::of_type<vk::component_mapping&>::for_elements_of(args...),
			.subresource_range = elements::of_type<vk::image_subresource_range&>::for_elements_of(args...)
		};

		VkImage image_view;

		vk::result result {
			(int32) vkCreateImageView(
				(VkDevice) device.value,
				(VkImageViewCreateInfo*) &ci,
				nullptr,
				(VkImageView*) &image_view
			)
		};

		if(!result.success()) return result;

		return vk::handle<vk::image_view>{ image_view };
	}

	template<typename... Args>
	vk::handle<vk::image_view> create_image_view(Args&&... args) {
		auto result = try_create_image_view(forward<Args>(args)...);
		if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
		return result.template get<vk::handle<vk::image_view>>();
	}

	
}