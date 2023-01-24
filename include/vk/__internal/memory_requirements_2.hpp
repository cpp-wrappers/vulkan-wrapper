#pragma once

#include "./memory_requirements.hpp"

namespace vk {

	struct memory_requirements_2 {
		uint32 structure_type = 1000146003;
		const void* next;
		vk::memory_requirements memory_requirements;
	};

} // vk