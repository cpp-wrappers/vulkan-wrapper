#pragma once

#include <core/flag_enum.hpp>

namespace vk {

	enum class dependency {
		by_region    = 0x00000001,
		device_group = 0x00000004,
		view_local   = 0x00000002
	};

	using dependencies = flag_enum<dependency>;

} // vk