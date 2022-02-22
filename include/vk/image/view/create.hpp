#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include "vk/create_or_allocate.hpp"
#include "vk/handle/get_value.hpp"
#include "vk/result.hpp"
#include "vk/handle/possibly_guarded_handle_of.hpp"
#include "vk/image/component_mapping.hpp"
#include "vk/image/subresource_range.hpp"

namespace vk {

	struct device;
	struct image_view;

	template<>
	struct vk::create_t<vk::image_view> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::image>,
			types::are_contain_one_decayed_same_as<vk::format>,
			types::are_contain_one_decayed_same_as<vk::image_view_type>,
			types::are_contain_one_decayed_same_as<vk::component_mapping>,
			types::are_contain_one_decayed_same_as<vk::image_subresource_range>
		>::for_types<Args...>
		vk::expected<vk::handle<vk::image_view>>
		operator () (Args&&... args) const {
			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);
			auto& image = elements::vk::possibly_guarded_handle_of<vk::image>(args...);

			vk::image_view_create_info ci {
				.image = vk::get_handle(image),
				.view_type = elements::decayed_same_as<vk::image_view_type>(args...),
				.format = elements::decayed_same_as<vk::format>(args...),
				.components = elements::decayed_same_as<vk::component_mapping>(args...),
				.subresource_range = elements::decayed_same_as<vk::image_subresource_range>(args...)
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