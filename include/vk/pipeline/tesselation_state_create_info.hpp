#pragma once

#include <core/integer.hpp>

namespace vk {

	struct pipeline_tesselation_state_create_info {
		uint32 structure_type = 21;
		const void* next = nullptr;
		uint32 patch_control_points;
	};

} // vk