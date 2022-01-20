#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/are_may_contain_one_type.hpp>
#include <core/types/are_contain_type.hpp>

#include "../../types/are_contain_one_possibly_guarded_handle_of.hpp"
#include "../../elements/possibly_guarded_handle_of.hpp"
#include "../sampler/handle.hpp"
#include "../image/view/handle.hpp"
#include "../image/layout.hpp"

namespace vk {

	struct descriptor_image_info {
		vk::handle<vk::sampler> sampler;
		vk::handle<vk::image_view> image_view;
		vk::image_layout image_layout{ vk::image_layout::undefined };

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::sampler>,
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::image_view>,
			types::are_may_contain_one_type<vk::image_layout>
		>::for_types_of<decay<Args>...>
		descriptor_image_info(Args&&... args)
		:
			sampler{ elements::vk::possibly_guarded_handle_of<vk::sampler>(args...) },
			image_view{ elements::vk::possibly_guarded_handle_of<vk::image_view>(args...) }
		{
			if constexpr(types::are_contain_type<vk::image_layout>::for_types_of<Args...>) {
				image_layout = elements::of_type<vk::image_layout>(args...);
			}
		}
	};

} // vk

static_assert(sizeof(vk::descriptor_image_info) == sizeof(VkDescriptorImageInfo));