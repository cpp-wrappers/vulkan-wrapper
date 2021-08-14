export module vk.extension_properties;

import vk_headers;

export namespace vk {

struct extension_properties {
	char name[VK_MAX_EXTENSION_NAME_SIZE];
	uint32_t spec_version;
};

}

static_assert(sizeof(vk::extension_properties) == sizeof(VkExtensionProperties));