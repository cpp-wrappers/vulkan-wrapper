#pragma once

#include <core/integer.hpp>

#include "../../shared/headers.hpp"

namespace vk {

	struct physical_device_sparse_properties {
		uint32 residency_standard_2d_block_shape;
		uint32 residency_standard_2d_multisample_block_shape;
		uint32 residency_standard_3d_blockShape;
		uint32 residency_aligned_mip_size;
		uint32 residency_non_resident_strict;
	};

} // vk

static_assert(sizeof(vk::physical_device_sparse_properties) == sizeof(VkPhysicalDeviceSparseProperties));