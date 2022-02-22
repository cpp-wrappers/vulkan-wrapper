#pragma once

#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

#include "vk/image/view/handle.hpp"
#include "vk/image/layout.hpp"
#include "vk/sampler/handle.hpp"
#include "vk/handle/possibly_guarded_handle_of.hpp"

namespace vk {

	struct descriptor_image_info {
		vk::handle<vk::sampler> sampler;
		vk::handle<vk::image_view> image_view;
		vk::image_layout image_layout{ vk::image_layout::undefined };

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::sampler>,
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::image_view>,
			types::are_may_contain_one_decayed_same_as<vk::image_layout>
		>::for_types<Args...>
		descriptor_image_info(Args&&... args)
		:
			sampler{ elements::vk::possibly_guarded_handle_of<vk::sampler>(args...) },
			image_view{ elements::vk::possibly_guarded_handle_of<vk::image_view>(args...) }
		{
			if constexpr(types::are_contain_decayed_same_as<vk::image_layout>::for_types<Args...>) {
				image_layout = elements::decayed_same_as<vk::image_layout>(args...);
			}
		}
	};

} // vk

static_assert(sizeof(vk::descriptor_image_info) == sizeof(VkDescriptorImageInfo));