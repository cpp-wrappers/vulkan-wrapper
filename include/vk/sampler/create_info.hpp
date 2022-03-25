#pragma once

#include "border_color.hpp"
#include "filter.hpp"
#include "mipmap_mode.hpp"
#include "address_mode.hpp"
#include "../compare_op.hpp"

#include <core/flag_enum.hpp>

namespace vk {

	enum class sampler_create_flag {
		subsampled                       = 0x00000001,
		subsampled_coarse_reconstruction = 0x00000002,
	};

	using sampler_create_flags = flag_enum<vk::sampler_create_flag>;

	struct mip_lod_bias : wrapper::of<float, struct mip_lod_bias_t> {};
	struct anisotropy_enable :
		wrapper::of<uint32, struct anisotropy_enable_t>
	{};
	struct max_anisotropy : wrapper::of<float, struct max_anisotropy_t> {};
	struct compare_enable : wrapper::of<uint32, struct compare_enable_t> {};
	struct min_lod : wrapper::of<float, struct min_lod_t> {};
	struct max_lod : wrapper::of<float, struct max_lod_t> {};
	struct unnormalized_coordinates :
		wrapper::of<uint32, struct unnormalized_coordinates_t>
	{};

	struct sampler_create_info {
		uint32 structure_type = 31;
		const void * next = nullptr;
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

	}; // sampler_create_info

} // vk