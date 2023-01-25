#pragma once

namespace vk {

	enum class acceleration_structure_build_type {
		host = 0,
		device = 1,
		host_or_device = 2
	};

	namespace as {
		using build_type = acceleration_structure_build_type;
	}

} // vk