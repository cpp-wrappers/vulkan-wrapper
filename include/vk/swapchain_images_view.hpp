#pragma once

#include "headers.hpp"
#include "image.hpp"
#include "ptr_to_ref_like.hpp"
#include "result.hpp"

namespace vk {

void view_swapchain_images(VkDevice device, VkSwapchainKHR swapchain, uint32_t count, auto&& f);

class swapchain_images_view {
	cursed::ptr_to_ref_like<vk::image> images;
	uint32_t count;

	swapchain_images_view(
		cursed::ptr_to_ref_like<vk::image> images,
		uint32_t count
	) : images{ images }, count { count }
	{}

	friend void view_swapchain_images(VkDevice device, VkSwapchainKHR swapchain, uint32_t count, auto&& f);

public:

	auto begin() const {
		return images;
	}

	auto end() const {
		return images + count;
	}
};

void view_swapchain_images(VkDevice device, VkSwapchainKHR swapchain, uint32_t count, auto&& f) {
	vk::image* images[count];

	vk::throw_if_error(
		vkGetSwapchainImagesKHR(
			device,
			swapchain,
			&count,
			(VkImage*)images
		)
	);

	swapchain_images_view v{ images, count };
	f(v);
}

}