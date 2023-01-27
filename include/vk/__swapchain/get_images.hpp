#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"
#include "../__image/handle.hpp"
#include "../__swapchain/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct get_swapchain_images_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::swapchain>::underlying_type swapchain,
		uint32* swapchain_image_count,
		handle<vk::image>::underlying_type* swapchain_images
	)> {
		static constexpr auto name = "vkGetSwapchainImagesKHR";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::swapchain>> == 1,
		count_of_range_of_decayed<handle<vk::image>> <= 1
	>
	vk::expected<vk::count>
	try_get_swapchain_images(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::swapchain> swapchain = a.template
			get_decayed_same_as<handle<vk::swapchain>>();

		auto& images = a.template get_range_of_decayed<handle<vk::image>>();

		uint32 count = images.size();

		vk::result result {
			vk::get_device_function<vk::get_swapchain_images_function>(
				instance, device
			)(
				device.underlying(),
				swapchain.underlying(),
				&count,
				(handle<vk::image>::underlying_type*) images.iterator()
			)
		};

		if(result.error()) return result;

		return vk::count{ count };

	} // try_get_swapchain_images

	template<typename... Args>
	vk::count get_swapchain_images(Args&&... args) {
		auto result = vk::try_get_swapchain_images(forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk