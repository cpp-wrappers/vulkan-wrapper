#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include "../../create_or_allocate.hpp"
#include "../../handle/get_value.hpp"
#include "../../result.hpp"
#include "../../device/handle.hpp"
#include "../../image/component_mapping.hpp"
#include "../../image/subresource_range.hpp"
#include "../../function.hpp"

#include <core/handle/possibly_guarded_of.hpp>

extern "C" VK_ATTR int32 VK_CALL vkCreateImageView(
	handle<vk::device> device,
	const vk::image_view_create_info* create_info,
	const void* allocator,
	handle<vk::image_view>* view
);

namespace vk {

	template<>
	struct vk::create_t<vk::image_view> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_contain_one_possibly_guarded_handle_of<vk::image>,
			types::are_contain_one_decayed<vk::format>,
			types::are_contain_one_decayed<vk::image_view_type>,
			types::are_may_contain_one_decayed<vk::component_mapping>,
			types::are_may_contain_one_decayed<vk::image_subresource_range>
		>::for_types<Args...>
		vk::expected<handle<vk::image_view>>
		operator () (Args&&... args) const {
			auto& device = elements::possibly_guarded_handle_of<
				vk::device
			>(args...);

			auto& image = elements::possibly_guarded_handle_of<
				vk::image
			>(args...);

			vk::image_view_create_info ci {
				.image = vk::get_handle(image),
				.view_type = elements::decayed<vk::image_view_type>(args...),
				.format = elements::decayed<vk::format>(args...)
			};

			if constexpr(
				types::are_contain_decayed<
					vk::component_mapping
				>::for_types<Args...>
			) {
				ci.components = elements::decayed<
					vk::component_mapping
				>(args...);
			}

			if constexpr(
				types::are_contain_decayed<
					vk::image_subresource_range
				>::for_types<Args...>
			) {
				ci.subresource_range = elements::decayed<
					vk::image_subresource_range
				>(args...);
			}

			handle<vk::image_view> image_view;

			vk::result result {
				vkCreateImageView(
					vk::get_handle(device),
					&ci,
					nullptr,
					&image_view
				)
			};

			if(result.error()) return result;

			return image_view;

		} // operator ()

	}; // create_t<image_view>

} // vk