#pragma once

#include <enum_flags.hpp>

namespace vk {

	enum class color_component {
		r = 0x00000001,
		g = 0x00000002,
		b = 0x00000004,
		a = 0x00000008
	};

	using color_components = enum_flags<vk::color_component>;

} // vk