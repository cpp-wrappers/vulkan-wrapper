#pragma once

#include "../sampler/handle.hpp"
#include "../image/view/handle.hpp"
#include "../image/layout.hpp"

namespace vk {

	struct descriptor_image_info {
		vk::handle<vk::sampler> sampler;
		vk::handle<vk::image_view> image_view;
		vk::image_layout image_layout;
	};

} // vk

static_assert(sizeof(vk::descriptor_image_info) == sizeof(VkDescriptorImageInfo));