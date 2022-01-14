#pragma once

#include <core/flag_enum.hpp>

#include "../../shared/headers.hpp"
#include "../../shared/compare_op.hpp"
#include "border_color.hpp"
#include "filter.hpp"
#include "mipmap_mode.hpp"
#include "address_mode.hpp"

namespace vk {

	enum class sampler_create_flag {
		subsampled = VK_SAMPLER_CREATE_SUBSAMPLED_BIT_EXT,
		subsampled_coarse_reconstruction = VK_SAMPLER_CREATE_SUBSAMPLED_COARSE_RECONSTRUCTION_BIT_EXT,
	};

	using sampler_create_flags = flag_enum<vk::sampler_create_flag>;

	struct mip_lod_bias : wrapper::of<float, struct mip_lod_bias_t> {};
	struct anisotropy_enable : wrapper::of<uint32, struct anisotropy_enable_t> {};
	struct max_anisotropy : wrapper::of<float, struct max_anisotropy_t> {};
	struct compare_enable : wrapper::of<uint32, struct compare_enable_t> {};
	struct min_lod : wrapper::of<float, struct min_lod_t> {};
	struct max_lod : wrapper::of<float, struct max_lod_t> {};
	struct unnormalized_coordinates : wrapper::of<uint32, struct unnormalized_coordinates_t> {};

	struct sampler_create_info {
		const uint32 type = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		const void * const next = nullptr;
		vk::sampler_create_flags flags;
		vk::mag_filter mag_filter;
		vk::min_filter min_filter;
		vk::mipmap_mode mipmap_mode;
		vk::address_mode_u address_mode_u;
		vk::address_mode_v address_mode_v;
		vk::address_mode_w address_mode_w;
		vk::mip_lod_bias mip_lod_bias;
		vk::anisotropy_enable anisotropy_enable;
		vk::max_anisotropy max_anisotropy;
		vk::compare_enable compare_enable;
		vk::compare_op compare_op;
		vk::min_lod min_lod;
		vk::max_lod max_lod;
		vk::border_color border_color;
		vk::unnormalized_coordinates unnormalized_coordinates;
	};

} // vk

static_assert(sizeof(vk::sampler_create_info) == sizeof(VkSamplerCreateInfo));
