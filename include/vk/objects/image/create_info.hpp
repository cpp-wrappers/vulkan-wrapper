#pragma once

#include <core/integer.hpp>
#include <core/flag_enum.hpp>

#include "../../shared/headers.hpp"
#include "../../shared/extent.hpp"
#include "../../shared/sample_count.hpp"
#include "../../shared/sharing_mode.hpp"
#include "../../shared/queue_family_index.hpp"
#include "../../shared/format.hpp"
#include "tiling.hpp"
#include "usage.hpp"
#include "layout.hpp"

namespace vk {

	enum class image_create_flag {
		sparse_binding_bit = VK_IMAGE_CREATE_SPARSE_BINDING_BIT,
		sparse_residency_bit = VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT,
		sparse_aliased_bit = VK_IMAGE_CREATE_SPARSE_ALIASED_BIT,
		mutable_format_bit = VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT,
		cube_compatible_bit = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT,
		alias_bit = VK_IMAGE_CREATE_ALIAS_BIT,
		split_instance_bind_regions_bit = VK_IMAGE_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT,
		two_d_array_compatible_bit = VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT,
		block_texel_view_compatible_bit = VK_IMAGE_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT,
		extended_usage_bit = VK_IMAGE_CREATE_EXTENDED_USAGE_BIT,
		protected_bit = VK_IMAGE_CREATE_PROTECTED_BIT,
		disjoint_bit = VK_IMAGE_CREATE_DISJOINT_BIT,
		corner_sampled_bit_nv = VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV,
		sample_locations_compatible_depth_bit_ext = VK_IMAGE_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT,
		subsampled_bit_ext = VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT,
		//fragment_density_map_offset_bit_qcom = VK_IMAGE_CREATE_FRAGMENT_DENSITY_MAP_OFFSET_BIT_QCOM,
		split_instance_bind_regions_bit_khr = VK_IMAGE_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT_KHR,
		block_texel_view_compatible_bit_khr = VK_IMAGE_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT_KHR,
		extended_usage_bit_khr = VK_IMAGE_CREATE_EXTENDED_USAGE_BIT_KHR,
		disjoint_bit_khr = VK_IMAGE_CREATE_DISJOINT_BIT_KHR,
		alias_bit_khr = VK_IMAGE_CREATE_ALIAS_BIT_KHR,
	};

	enum class image_type {
		one_d = VK_IMAGE_VIEW_TYPE_1D,
		two_d = VK_IMAGE_VIEW_TYPE_2D,
		three_d = VK_IMAGE_VIEW_TYPE_3D
	};

	using image_create_flags = flag_enum<vk::image_create_flag>;

	struct mip_levels : wrapper::of_integer<uint32, struct mip_levels_t> {};
	struct array_layers : wrapper::of_integer<uint32, struct array_layers_t> {};
	
	struct image_create_info {
		uint32 const type = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		void * const next;
		vk::image_create_flags flags;
		vk::image_type image_type;
		vk::format format;
		vk::extent<3> extent;
		vk::mip_levels mip_levels;
		vk::array_layers array_layers;
		vk::sample_count samples;
		vk::image_tiling tiling;
		vk::image_usages usages;
		vk::sharing_mode sharing_mode;
		uint32 queue_family_index_count;
		vk::queue_family_index const * queue_family_indices;
		vk::initial_layout initial_layout;
	};

} // vk

static_assert(sizeof(vk::image_create_info) == sizeof(VkImageCreateInfo));