#pragma once

#include "../../../object/create_or_allocate.hpp"
#include "../../../object/handle/get_value.hpp"
#include "../../../types/are_contain_one_possibly_guarded_handle_of.hpp"
#include "../../../elements/possibly_guarded_handle_of.hpp"
#include "../../../shared/result.hpp"
#include "../component_mapping.hpp"
#include "../subresource_range.hpp"
#include "handle.hpp"
#include "create_info.hpp"

namespace vk {

	struct device;
	struct image_view;

	template<>
	struct vk::create_t<vk::image_view> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::image>,
			types::count_of_type<vk::format>::equals<1>,
			types::count_of_type<vk::image_view_type>::equals<1>,
			types::count_of_type<vk::component_mapping>::equals<1>,
			types::count_of_type<vk::image_subresource_range>::equals<1>
		>::for_types_of<decay<Args>...>
		vk::expected<vk::handle<vk::image_view>>
		operator () (Args&&... args) const {
			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);
			auto& image = elements::vk::possibly_guarded_handle_of<vk::image>(args...);

			vk::image_view_create_info ci {
				.image = vk::get_handle(image),
				.view_type = elements::of_type<vk::image_view_type>(args...),
				.format = elements::of_type<vk::format>(args...),
				.components = elements::of_type<vk::component_mapping>(args...),
				.subresource_range = elements::of_type<vk::image_subresource_range>(args...)
			};

			vk::handle<vk::image_view> image_view;

			vk::result result {
				(int32) vkCreateImageView(
					(VkDevice) vk::get_handle_value(device),
					(VkImageViewCreateInfo*) &ci,
					(VkAllocationCallbacks*) nullptr,
					(VkImageView*) &image_view
				)
			};

			if(result.error()) return result;

			return image_view;
		}

	};

} // vk