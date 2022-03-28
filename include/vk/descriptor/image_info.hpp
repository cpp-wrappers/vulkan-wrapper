#pragma once

#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/handle/possibly_guarded_of.hpp>

#include "../handle/get.hpp"
#include "../image/view/handle.hpp"
#include "../image/layout.hpp"
#include "../sampler/handle.hpp"

namespace vk {

	struct descriptor_image_info {
		handle<vk::sampler> sampler;
		handle<vk::image_view> image_view;
		vk::image_layout image_layout{ vk::image_layout::undefined };

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_may_contain_one_possibly_guarded_handle_of<vk::sampler>,
			types::are_contain_one_possibly_guarded_handle_of<vk::image_view>,
			types::are_may_contain_one_decayed<vk::image_layout>
		>::for_types<Args...>
		descriptor_image_info(Args&&... args) :
			image_view{ vk::get_handle(
				elements::possibly_guarded_handle_of<vk::image_view>(args...)
			)}
		{
			if constexpr(
				types::are_contain_possibly_guarded_handle_of<
					vk::sampler
				>::for_types<Args...>
			) {
				sampler = vk::get_handle(
					elements::possibly_guarded_handle_of<vk::sampler>(args...)
				);
			}
			if constexpr(
				types::are_contain_decayed<vk::image_layout>::for_types<Args...>
			) { image_layout = elements::decayed<vk::image_layout>(args...); }

		} // constructor

	}; // descriptor_image_info

} // vk