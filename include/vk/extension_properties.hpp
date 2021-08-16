#pragma once

#include "headers.hpp"

namespace vk {

struct extension_properties {
	char name[VK_MAX_EXTENSION_NAME_SIZE];
	uint32_t spec_version;
};

} // vk

static_assert(sizeof(vk::extension_properties) == sizeof(VkExtensionProperties));