#pragma once

#include "application_info.hpp"

#include "../extension.hpp"
#include "../layer_name.hpp"

namespace vk {
	
	struct instance_create_info {
		uint32                      structure_type = 1;
		const void*                 next;
		uint32                      flags;
		const vk::application_info* application_info;
		uint32                      enabled_layer_count;
		const vk::layer*            enabled_layer_names;
		uint32                      enabled_extension_count;
		const vk::extension*        enabled_extension_names;
	};
	
} // vk