#pragma once

#include "headers.hpp"
#include <core/integer.hpp>

namespace vk {

	struct extension_properties {
		char name[VK_MAX_EXTENSION_NAME_SIZE];
		uint32 spec_version;
	};

} // vk

static_assert(sizeof(vk::extension_properties) == sizeof(VkExtensionProperties));