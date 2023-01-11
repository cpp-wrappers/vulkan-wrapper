#pragma once

#include "application_info.hpp"

#include "../__internal/extension_name.hpp"
#include "../__internal/layer_name.hpp"

namespace vk {
	
	struct instance_create_info {
		uint32                      structure_type = 1;
		const void*                 next = nullptr;
		uint32                      flags = 0;
		const vk::application_info* application_info = nullptr;
		uint32                      enabled_layer_count = 0;
		const vk::layer_name*       enabled_layer_names = nullptr;
		uint32                      enabled_extension_count = 0;
		const vk::extension_name*   enabled_extension_names = nullptr;
	};
	
} // vk