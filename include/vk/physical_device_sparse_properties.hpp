export module vk.physical_device_sparse_properties;

export import <cinttypes>;
import vk_headers;

export namespace vk {

struct physical_device_sparse_properties {
	uint32_t residencyStandard2DBlockShape;
	uint32_t residencyStandard2DMultisampleBlockShape;
	uint32_t residencyStandard3DBlockShape;
	uint32_t residencyAlignedMipSize;
	uint32_t residencyNonResidentStrict;
};

}

static_assert(
	sizeof(vk::physical_device_sparse_properties)
	==
	sizeof(VkPhysicalDeviceSparseProperties)
);