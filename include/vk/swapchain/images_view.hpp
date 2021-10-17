#pragma once

#include "../headers.hpp"
#include "../image/image.hpp"
#include "../ptr_to_ref_like.hpp"
#include "../result.hpp"
#include <vulkan/vulkan_core.h>

namespace vk {

struct device;
struct swapchain;

void view_swapchain_images(vk::device& device, vk::swapchain& swapchain, uint32 count, auto&& f);

class swapchain_images_view {
	cursed::ptr_to_ref_like<vk::image> images;
	uint32 count;

	swapchain_images_view(
		cursed::ptr_to_ref_like<vk::image> images,
		uint32 count
	) : images{ images }, count { count }
	{}

	friend void view_swapchain_images(const vk::device& device, const vk::swapchain& swapchain, uint32 count, auto&& f);

public:

	auto begin() const {
		return images;
	}

	auto end() const {
		return images + count;
	}

	auto& front() const {
		return *begin();
	}
};

void view_swapchain_images(const vk::device& device, const vk::swapchain& swapchain, uint32 count, auto&& f) {
	vk::image* images[(primitive::uint32)count];

	vk::throw_if_error(
		vkGetSwapchainImagesKHR(
			(VkDevice) &device,
			(VkSwapchainKHR) &swapchain,
			(primitive::uint32 *) &count,
			(VkImage*)images
		)
	);

	swapchain_images_view v{ images, count };
	f(v);
}

}