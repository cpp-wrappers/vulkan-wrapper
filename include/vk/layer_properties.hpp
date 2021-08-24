#pragma once

#include "headers.hpp"
#include <cstdint>

namespace vk {

struct layer_properties {
	char name[VK_MAX_EXTENSION_NAME_SIZE];
	uint32_t spec_version;
	uint32_t implementation_version;
	char description[VK_MAX_DESCRIPTION_SIZE];
};

} // vk

static_assert(sizeof(vk::layer_properties) == sizeof(VkLayerProperties));