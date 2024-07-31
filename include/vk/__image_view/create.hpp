#pragma once

#include "./handle.hpp"
#include "./create_info.hpp"
#include "../__internal/function.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__device/handle.hpp"
#include "../__instance/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct create_image_view_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		const vk::image_view_create_info* create_info,
		const void* allocator,
		handle<vk::image_view>::underlying_type* view
	)> {
		static constexpr auto name = "vkCreateImageView";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::image>>.decayed == 1,
		is_same_as<vk::format>.decayed == 1,
		is_same_as<vk::image_view_type>.decayed == 1,
		is_same_as<vk::component_mapping>.decayed <= 1,
		is_same_as<vk::image_subresource_range>.decayed <= 1
	>
	vk::expected<handle<vk::image_view>>
	try_create_image_view(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::image> image = a.template
			get<is_same_as<handle<vk::image>>.decayed>();

		vk::image_view_create_info ci {
			.image = image.underlying(),
			.view_type = a.template get<is_same_as<vk::image_view_type>.decayed>(),
			.format = a.template get<is_same_as<vk::format>.decayed>()
		};

		if constexpr (
			(is_same_as<vk::component_mapping>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.components = a.template
				get<is_same_as<vk::component_mapping>.decayed>();
		}

		if constexpr (
			(is_same_as<vk::image_subresource_range> > 0).for_types<Args...>()
		) {
			ci.subresource_range = a.template
				get<is_same_as<vk::image_subresource_range>.decayed>();
		}

		handle<vk::image_view> image_view;

		vk::result result {
			vk::get_device_function<vk::create_image_view_function>(
				instance, device
			)(
				device.underlying(),
				&ci,
				nullptr,
				&image_view.underlying()
			)
		};

		if(result.error()) return result;

		return image_view;
	}

	template<typename... Args>
	handle<vk::image_view> create_image_view(Args&&... args) {
		vk::expected<handle<vk::image_view>> result
			= vk::try_create_image_view(forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk