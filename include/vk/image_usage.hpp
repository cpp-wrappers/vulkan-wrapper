#pragma once

#include "headers.hpp"

namespace vk {

enum class image_usage {
	transfer_src_bit = VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
	transfer_dst_bit = VK_IMAGE_USAGE_TRANSFER_DST_BIT,
	sampled_bit = VK_IMAGE_USAGE_SAMPLED_BIT,
	storage_bit = VK_IMAGE_USAGE_STORAGE_BIT,
	color_attachment_bit = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
	depth_stencil_attachment_bit = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
	transient_attachment_bit = VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT,
	input_attachment_bit = VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT,
	fragment_density_map_bit_ext = VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT,
	fragment_shading_rate_attachment_bit_khr = VK_IMAGE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR,
	invocation_mask_bit_huawei = VK_IMAGE_USAGE_INVOCATION_MASK_BIT_HUAWEI,
	shading_rate_image_bit_nv = VK_IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV
};

} // vk