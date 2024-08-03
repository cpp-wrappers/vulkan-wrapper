#pragma once

#include "../__image_view/handle.hpp"
#include "../__image/layout.hpp"
#include "../__sampler/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct descriptor_image_info {
		handle<vk::sampler>::underlying_type sampler{};
		handle<vk::image_view>::underlying_type image_view{};
		vk::image_layout image_layout{ vk::image_layout::undefined };

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			is_same_as<handle<vk::sampler>> <= 1,
			is_same_as<handle<vk::image_view>> == 1,
			is_same_as<vk::image_layout> <= 1
		>
		descriptor_image_info(Args... args) {
			tuple<Args...> a { args... };

			image_view = a.template
				get<is_same_as<handle<vk::image_view>>>().underlying();

			if constexpr (
				(is_same_as<handle<vk::sampler>> > 0)
				.for_types<Args...>()
			) {
				sampler = a.template
					get<is_same_as<handle<vk::sampler>>>().underlying();
			}

			if constexpr (
				(is_same_as<vk::image_layout> > 0)
				.for_types<Args...>()
			) {
				image_layout = a.template get<is_same_as<vk::image_layout>>();
			}

		} // constructor

	}; // descriptor_image_info

} // vk