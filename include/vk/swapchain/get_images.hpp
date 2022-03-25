#pragma once

#include "handle.hpp"
#include "../unexpected_handler.hpp"

#include <core/range/of_value_type_same_as.hpp>

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_contain_one_possibly_guarded_handle_of<vk::swapchain>,
		types::are_contain_range_of<handle<vk::image>>
	>::for_types<Args...>
	vk::expected<vk::count>
	try_get_swapchain_images(Args&&... args) {
		auto& device = elements::possibly_guarded_handle_of<
			vk::device
		>(args...);

		auto& swapchain = elements::possibly_guarded_handle_of<
			vk::swapchain
		>(args...);

		auto& images = elements::range_of<handle<vk::image>>(args...);

		uint32 count = images.size();

		vk::result result {
			(int32) vkGetSwapchainImagesKHR(
				(VkDevice) vk::get_handle_value(device),
				(VkSwapchainKHR) vk::get_handle_value(swapchain),
				&count,
				(VkImage*) images.data()
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

template<typename... Args>
vk::count handle<vk::swapchain>::get_images(Args&&... args) const {
	return vk::get_swapchain_images(*this, forward<Args>(args)...);
}