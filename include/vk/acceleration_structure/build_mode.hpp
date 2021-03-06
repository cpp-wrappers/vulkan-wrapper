#pragma once

namespace vk {

	enum class acceleration_structure_build_mode {
		build = 0,
		update = 1
	};

	namespace as {
		using build_mode = vk::acceleration_structure_build_mode;
	}

} // vk