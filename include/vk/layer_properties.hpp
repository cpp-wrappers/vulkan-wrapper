#pragma once

#include <core/integer.hpp>

#include "headers.hpp"

namespace vk {

	struct layer_properties {
		char name[VK_MAX_EXTENSION_NAME_SIZE];
		uint32 spec_version;
		uint32 implementation_version;
		char description[VK_MAX_DESCRIPTION_SIZE];
	};

} // vk

static_assert(sizeof(vk::layer_properties) == sizeof(VkLayerProperties));