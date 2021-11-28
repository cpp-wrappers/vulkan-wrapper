#pragma once

#include "../shared/headers.hpp"

namespace vk {

enum class image_usage {
	transfer_src = VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
	transfer_dst = VK_IMAGE_USAGE_TRANSFER_DST_BIT,
	sampled = VK_IMAGE_USAGE_SAMPLED_BIT,
	storage = VK_IMAGE_USAGE_STORAGE_BIT,
	color_attachment = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
	depth_stencil_attachment = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
	transient_attachment = VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT,
	input_attachment = VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT,
	fragment_density_map_ext = VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT,
	fragment_shading_rate_attachment_khr = VK_IMAGE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR,
	//invocation_mask_huawei = VK_IMAGE_USAGE_INVOCATION_MASK_BIT_HUAWEI,
	shading_rate_image_nv = VK_IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV
};

} // vk