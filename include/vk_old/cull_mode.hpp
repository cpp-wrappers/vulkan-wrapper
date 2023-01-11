#pragma once

namespace vk {

	enum class cull_mode {
		none           = 0,
		front          = 0x00000001,
		back           = 0x00000002,
		front_and_back = 0x00000003
	};

} // vk