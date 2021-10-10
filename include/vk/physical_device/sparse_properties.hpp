#pragma once

#include "../headers.hpp"
#include <core/integer.hpp>

namespace vk {

struct physical_device_sparse_properties {
	uint32 residencyStandard2DBlockShape;
	uint32 residencyStandard2DMultisampleBlockShape;
	uint32 residencyStandard3DBlockShape;
	uint32 residencyAlignedMipSize;
	uint32 residencyNonResidentStrict;
};

}

static_assert(sizeof(vk::physical_device_sparse_properties) == sizeof(VkPhysicalDeviceSparseProperties));