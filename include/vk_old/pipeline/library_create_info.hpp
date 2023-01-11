#pragma once

#include "handle.hpp"

namespace vk {

	struct pipeline_library_create_info {
		uint32                      structure_type = 1000290000;
		const void*                 next;
		uint32                      library_count;
		const handle<vk::pipeline>* libraries;
	};

} // vk