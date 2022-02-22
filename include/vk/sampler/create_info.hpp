#pragma once

#include "border_color.hpp"
#include "filter.hpp"
#include "mipmap_mode.hpp"
#include "address_mode.hpp"

#include <core/flag_enum.hpp>

#include "vk/headers.hpp"
#include "vk/compare_op.hpp"

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
		vk::mip_lod_bias mip_lod_bias{ 0.0F };
		vk::anisotropy_enable anisotropy_enable{ false };
		vk::max_anisotropy max_anisotropy{ 0.0F };
		vk::compare_enable compare_enable{ false };
		vk::compare_op compare_op{ vk::compare_op::always };
		vk::min_lod min_lod{ 0.0 };
		vk::max_lod max_lod{ 0.0 };
		vk::border_color border_color{ vk::border_color::float_transparent_black };
		vk::unnormalized_coordinates unnormalized_coordinates{ false };
	};

} // vk

static_assert(sizeof(vk::sampler_create_info) == sizeof(VkSamplerCreateInfo));
