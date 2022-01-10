#pragma once

#include <core/wrapper/of.hpp>

#include "../../shared/headers.hpp"

namespace vk {

	enum class image_layout {
		undefined = VK_IMAGE_LAYOUT_UNDEFINED,
		general = VK_IMAGE_LAYOUT_GENERAL,
		color_attachment_optimal = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		depth_stencil_attachment_optimal = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
		depth_stencil_read_only_optimal = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
		shader_read_only_optimal = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		transfer_src_optimal = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
		transfer_dst_optimal = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		preinitialized = VK_IMAGE_LAYOUT_PREINITIALIZED,
		depth_read_only_stencil_attachment_optimal = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL,
		depth_attachment_stencil_read_only_optimal = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL,
		depth_attachment_optimal = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,
		depth_read_only_optimal = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
		stencil_attachment_optimal = VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL,
		stencil_read_only_optimal = VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL,
		present_src_khr = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
		shared_present_khr = VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR,
		fragment_density_map_optimal_ext = VK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT,
		fragment_shading_rate_attachment_optimal_khr = VK_IMAGE_LAYOUT_FRAGMENT_SHADING_RATE_ATTACHMENT_OPTIMAL_KHR,
		//read_only_optimal_khr = VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL_KHR,
		//attachment_optimal_khr = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR,
		depth_read_only_stencil_attachment_optimal_khr = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL_KHR,
		depth_attachment_stencil_read_only_optimal_khr = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL_KHR,
		shading_rate_optimal_nv = VK_IMAGE_LAYOUT_SHADING_RATE_OPTIMAL_NV,
		depth_attachment_optimal_khr = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL_KHR,
		depth_read_only_optimal_khr = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL_KHR,
		stencil_attachment_optimal_khr = VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL_KHR,
		stencil_read_only_optimal_khr = VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL_KHR,
	};

	struct initial_layout : wrapper::of<vk::image_layout> {};
	struct final_layout : wrapper::of<vk::image_layout> {};

}