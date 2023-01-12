#pragma once

#include "features.hpp"

namespace vk {

	struct physical_device_features_2 {
		uint32 structure_type = 1000059000;
		const void* next;
		vk::physical_device_features features;
	};

} // vk