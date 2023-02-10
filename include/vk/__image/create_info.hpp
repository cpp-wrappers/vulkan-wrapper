#pragma once

#include "./tiling.hpp"
#include "./usage.hpp"
#include "./layout.hpp"
#include "../__internal/format.hpp"
#include "../__internal/extent.hpp"
#include "../__internal/sample_count.hpp"
#include "../__internal/sharing_mode.hpp"
#include "../__internal/queue_family_index.hpp"

#include <enum_flags.hpp>

namespace vk {

	enum class image_create_flag {
		sparse_binding                    = 0x00000001,
		sparse_residency                  = 0x00000002,
		sparse_aliased                    = 0x00000004,
		mutable_format                    = 0x00000008,
		cube_compatible                   = 0x00000010,
		alias                             = 0x00000400,
		split_instance_bind_regions       = 0x00000040,
		two_d_array_compatible            = 0x00000020,
		block_texel_view_compatible       = 0x00000080,
		extended                          = 0x00000100,
		_protected                        = 0x00000800,
		disjoint                          = 0x00000200,
		corner_sampled                    = 0x00002000,
		sample_locations_compatible_depth = 0x00001000,
		subsampled                        = 0x00004000,
		fragment_density_map_offset       = 0x00008000
	};

	enum class image_type {
		one_d, two_d, three_d
	};

	using image_create_flags = enum_flags<vk::image_create_flag>;

	struct mip_levels   { uint32 _; };
	struct array_layers { uint32 _; };
	
	struct image_create_info {
		uint32                        structure_type = 14;
		void*                         next = nullptr;
		vk::image_create_flags        flags;
		vk::image_type                image_type;
		vk::format                    format;
		vk::extent<3>                 extent;
		vk::mip_levels                mip_levels { 1 };
		vk::array_layers              array_layers { 1 };
		vk::sample_count              samples { 1 };
		vk::image_tiling              tiling;
		vk::image_usages              usages;
		vk::sharing_mode              sharing_mode { sharing_mode::exclusive };
		uint32                        queue_family_index_count{};
		const vk::queue_family_index* queue_family_indices{};
		vk::initial_layout            initial_layout {
			image_layout::undefined
		};

	}; // image_create_info

} // vk