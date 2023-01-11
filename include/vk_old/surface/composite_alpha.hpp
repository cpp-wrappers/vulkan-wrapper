#pragma once

namespace vk {

	enum class composite_alpha {
		opaque          = 0x00000001,
		pre_multiplied  = 0x00000002,
		post_multiplied = 0x00000004,
		inherit         = 0x00000008
	};

} // vk