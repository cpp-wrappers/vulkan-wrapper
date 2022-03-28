#pragma once

namespace vk {

	enum class acceleration_structure_type {
		top_level    = 0,
		bottom_level = 1,
		generic      = 2
	};

	namespace as {
		using type = vk::acceleration_structure_type;
	}

} // vk